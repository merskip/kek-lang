//
// Created by Piotr Merski on 19.10.2019.
//

#include "NodeASTParser.h"
#include "ParsingException.h"
#include "NodeAST/FileNodeAST.h"

#include <memory>

std::unique_ptr<NodeAST> NodeASTParser::parse() {
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
        case Token::identifier:
            return parseReferenceOrCall();
        case Token::number:
            return parseNumber();
        default:
            throw ParsingException(currentOffset, "Unexpected token");
    }
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
    moveToNextToken(); // Eat (

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







