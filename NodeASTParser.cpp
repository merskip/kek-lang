//
// Created by Piotr Merski on 19.10.2019.
//

#include "NodeASTParser.h"
#include "ParsingException.h"
#include "NodeAST/FileNodeAST.h"
#include "NodeAST/FunctionBodyNodeAST.h"

#include <memory>

std::unique_ptr<FileNodeAST> NodeASTParser::parse() {
    parsedNodes.clear();
    do {
        moveToNextToken();
        auto parsedToken = parseToken();
        if (parsedToken)
            parsedNodes.push_back(std::move(parsedToken));
    } while (existsNextToken());
    return std::make_unique<FileNodeAST>(FileNodeAST(parsedNodes));
}

std::unique_ptr<NodeAST> NodeASTParser::parseToken(int minPrecedence) {
    auto parsedNode = parseCurrentToken();
    if (moveToNextIf([&](Token &nextToken) {
        if (nextToken.type != Token::Operator)
            return false;
        auto precedence = operatorsPrecedence[nextToken.text];
        return precedence > minPrecedence;
    })) {
        return parseOperator(std::move(parsedNode));
    }
    return parsedNode;
}

std::unique_ptr<NodeAST> NodeASTParser::parseCurrentToken() {
    switch (currentToken.type) {
        case Token::Eof:
            return nullptr;
        case Token::LeftParenthesis:
            return parseParentheses();
        case Token::Identifier:
            return parseReferenceOrCall();
        case Token::Number:
            return parseNumber();
        case Token::Func:
            return parseFunctionDefinition();
        case Token::Operator: {
            auto lhs = std::move(parsedNodes.back());
            parsedNodes.pop_back();
            return parseOperator(std::move(lhs));
        }
        default:
            throw ParsingException(currentOffset, "Unexpected token");
    }
}

std::unique_ptr<BinaryOperatorNodeAST> NodeASTParser::parseOperator(std::unique_ptr<NodeAST> lhs) {
    auto operatorText = currentToken.text;
    auto precedence = operatorsPrecedence[operatorText];

    moveToNextToken();
    auto rhs = parseToken(precedence);
    return std::make_unique<BinaryOperatorNodeAST>(BinaryOperatorNodeAST(operatorText, lhs, rhs));
}

std::unique_ptr<NodeAST> NodeASTParser::parseParentheses() {
    moveToNextToken(); // Consume (
    auto token = parseToken();
    if (!token)
        return nullptr;

    moveToNextToken();
    if (currentToken.type != Token::Type::RightParenthesis)
        throw ParsingException(currentOffset, "expected ')'");

    return token;
}

std::unique_ptr<NumberNodeAST> NodeASTParser::parseNumber() {
    return std::make_unique<NumberNodeAST>(currentToken.numberValue);
}

std::unique_ptr<NodeAST> NodeASTParser::parseReferenceOrCall() {
    if (isCallNode()) {
        return parseCall();
    } else {
        return parseReference();
    }
}

bool NodeASTParser::isCallNode() {
    return existsNextToken() && getNextToken().type == Token::Type::LeftParenthesis;
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
        if (currentToken.type == Token::Type::RightParenthesis)
            break;

        auto argumentNode = parseToken();
        arguments.push_back(std::move(argumentNode));

        moveToNextToken();
        if (currentToken.type == Token::Type::RightParenthesis)
            break;
        if (currentToken.type != Token::Type::Comma)
            throw ParsingException(currentOffset, "Expected , or )");
    }

    return std::make_unique<CallNodeAST>(CallNodeAST(callee, arguments));
}

std::unique_ptr<FunctionDefinitionNodeAST> NodeASTParser::parseFunctionDefinition() {
    auto prototype = parseFunctionPrototype();

    moveToNextToken();
    if (currentToken.type != Token::Type::LeftBracket)
        throw ParsingException(currentOffset, "Expected {");

    std::vector<std::unique_ptr<NodeAST>> nodes;
    while (true) {
        moveToNextToken();
        if (currentToken.type == Token::Type::RightBracket)
            break;

        auto node = parseToken();
        nodes.push_back(std::move(node));

        moveToNextToken();
        if (currentToken.type == Token::Type::RightBracket)
            break;
        if (currentToken.type != Token::Type::Semicolon)
            throw ParsingException(currentOffset, "Expected ; or }");
    }

    auto body = std::make_unique<FunctionBodyNodeAST>(FunctionBodyNodeAST(nodes));
    return std::make_unique<FunctionDefinitionNodeAST>(FunctionDefinitionNodeAST(prototype, body));
}

std::unique_ptr<FunctionPrototypeNodeAST> NodeASTParser::parseFunctionPrototype() {
    moveToNextToken(); // Consume 'func'

    if (currentToken.type != Token::Type::Identifier)
        throw ParsingException(currentOffset, "Expected function identifier");

    auto name = currentToken.text;

    moveToNextToken();
    if (currentToken.type != Token::Type::LeftParenthesis)
        throw ParsingException(currentOffset, "Expected (");

    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;
    while (true) {
        moveToNextToken();
        if (currentToken.type == Token::Type::RightParenthesis)
            break;
        if (currentToken.type != Token::Type::Identifier)
            throw ParsingException(currentOffset, "Expected identifier or )");

        auto argumentReference = parseReference();
        arguments.push_back(std::move(argumentReference));

        moveToNextToken();
        if (currentToken.type == Token::Type::RightParenthesis)
            break;
        if (currentToken.type != Token::Type::Comma)
            throw ParsingException(currentOffset, "Expected , or )");
    }
    return std::make_unique<FunctionPrototypeNodeAST>(FunctionPrototypeNodeAST(name, arguments));
}

bool NodeASTParser::moveToNextIf(const std::function<bool(Token &)> &predicate) {
    if (existsNextToken()) {
        auto nextToken = getNextToken();
        if (predicate(nextToken)) {
            moveToNextToken();
            return true;
        }
    }
    return false;
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
