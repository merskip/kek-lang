//
// Created by Piotr Merski on 19.10.2019.
//

#include "NodeASTParser.h"
#include "ParsingException.h"
#include "NodeAST/FileNodeAST.h"
#include "NodeAST/FunctionBodyNodeAST.h"

#include <memory>

std::unique_ptr<FileNodeAST> NodeASTParser::parse() {
    std::vector<std::unique_ptr<NodeAST>> nodes;
    do {
        moveToNextToken();
        auto parsedToken = parseToken();
        if (parsedToken)
            nodes.push_back(std::move(parsedToken));
    } while (existsNextToken());
    return std::make_unique<FileNodeAST>(FileNodeAST(nodes));
}

std::unique_ptr<NodeAST> NodeASTParser::parseToken() {
    switch (currentToken.type) {
        case Token::eof:
            return nullptr;
        case Token::leftParenthesis:
            return parseParentheses();
        case Token::identifier:
            return parseReferenceOrCall();
        case Token::number:
            return parseNumber();
        case Token::func:
            return parseFunctionDefinition();
        default:
            throw ParsingException(currentOffset, "Unexpected token");
    }
}

std::unique_ptr<NodeAST> NodeASTParser::parseParentheses() {
    moveToNextToken(); // Consume (
    auto token = parseToken();
    if (!token)
        return nullptr;

    moveToNextToken();
    if (currentToken.type != Token::Type::rightParenthesis)
        throw ParsingException(currentOffset, "expected ')'");

    return token;
}

std::unique_ptr<NumberNodeAST> NodeASTParser::parseNumber() {
    return std::make_unique<NumberNodeAST>(NumberNodeAST(currentToken.numberValue));
}

std::unique_ptr<NodeAST> NodeASTParser::parseReferenceOrCall() {
    if (isCallNode()) {
        return parseCall();
    } else {
        return parseReference();
    }
}

bool NodeASTParser::isCallNode() {
    return existsNextToken() && getNextToken().type == Token::Type::leftParenthesis;
}

std::unique_ptr<ReferenceNodeAST> NodeASTParser::parseReference() {
    return std::make_unique<ReferenceNodeAST>(ReferenceNodeAST(currentToken.text));
}

std::unique_ptr<CallNodeAST> NodeASTParser::parseCall() {
    auto callee = currentToken.text;
    moveToNextToken(); // Consume (

    std::vector<std::unique_ptr<NodeAST>> arguments;
    while (true) {
        moveToNextToken();
        if (currentToken.type == Token::Type::rightParenthesis)
            break;

        auto argumentNode = parseToken();
        arguments.push_back(std::move(argumentNode));

        moveToNextToken();
        if (currentToken.type == Token::Type::rightParenthesis)
            break;
        if (currentToken.type != Token::Type::comma)
            throw ParsingException(currentOffset, "Expected , or )");
    }

    return std::make_unique<CallNodeAST>(CallNodeAST(callee, arguments));
}

std::unique_ptr<FunctionDefinitionNodeAST> NodeASTParser::parseFunctionDefinition() {
    auto prototype = parseFunctionPrototype();

    moveToNextToken();
    if (currentToken.type != Token::Type::leftBracket)
        throw ParsingException(currentOffset, "Expected {");

    std::vector<std::unique_ptr<NodeAST>> nodes;
    while (true) {
        moveToNextToken();
        if (currentToken.type == Token::Type::rightBracket)
            break;

        auto node = parseToken();
        nodes.push_back(std::move(node));

        moveToNextToken();
        if (currentToken.type == Token::Type::rightBracket)
            break;
        if (currentToken.type != Token::Type::semicolon)
            throw ParsingException(currentOffset, "Expected ; or }");
    }

    auto body = std::make_unique<FunctionBodyNodeAST>(FunctionBodyNodeAST(nodes));
    return std::make_unique<FunctionDefinitionNodeAST>(FunctionDefinitionNodeAST(prototype, body));
}

std::unique_ptr<FunctionPrototypeNodeAST> NodeASTParser::parseFunctionPrototype() {
    moveToNextToken(); // Consume 'func'

    if (currentToken.type != Token::Type::identifier)
        throw ParsingException(currentOffset, "Expected function identifier");

    auto name = currentToken.text;

    moveToNextToken();
    if (currentToken.type != Token::Type::leftParenthesis)
        throw ParsingException(currentOffset, "Expected (");

    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;
    while (true) {
        moveToNextToken();
        if (currentToken.type == Token::Type::rightParenthesis)
            break;
        if (currentToken.type != Token::Type::identifier)
            throw ParsingException(currentOffset, "Expected identifier or )");

        auto argumentReference = parseReference();
        arguments.push_back(std::move(argumentReference));

        moveToNextToken();
        if (currentToken.type == Token::Type::rightParenthesis)
            break;
        if (currentToken.type != Token::Type::comma)
            throw ParsingException(currentOffset, "Expected , or )");
    }
    return std::make_unique<FunctionPrototypeNodeAST>(FunctionPrototypeNodeAST(name, arguments));
}

void NodeASTParser::moveToNextToken() {
    currentToken = getNextToken();
    currentOffset++;
}

bool NodeASTParser::existsNextToken() {
    return currentOffset + 1 < tokens.size();
}

Token &NodeASTParser::getNextToken() {
    return *std::next(tokens.begin(), currentOffset + 1);
}
