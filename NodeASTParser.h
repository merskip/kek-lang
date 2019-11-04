//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <list>
#include <memory>
#include <functional>
#include "Lexer/Token.h"
#include "NodeAST/NodeAST.h"
#include "NodeAST/NumberNodeAST.h"
#include "NodeAST/ReferenceNodeAST.h"
#include "NodeAST/CallNodeAST.h"
#include "NodeAST/FunctionDefinitionNodeAST.h"
#include "NodeAST/FileNodeAST.h"
#include "NodeAST/BinaryOperatorNodeAST.h"

class NodeASTParser {

private:
    std::list<Token> tokens;
    long currentOffset = -1;
    Token &currentToken;
    std::vector<std::unique_ptr<NodeAST>> parsedNodes;

    std::map<std::string, int> operatorsPrecedence;

public:
    explicit NodeASTParser(std::list<Token> &tokens)
            : tokens(tokens), currentToken(*tokens.begin()) {
        addOperatorPrecedence("+", 100);
        addOperatorPrecedence("-", 100);
        addOperatorPrecedence("*", 500);
        addOperatorPrecedence("/", 500);
    }

    void addOperatorPrecedence(const std::string &operatorText, int precedence) {
        operatorsPrecedence[operatorText] = precedence;
    }

    std::unique_ptr<FileNodeAST> parse();

private:

    std::unique_ptr<NodeAST> parseToken(int minPrecedence = 0);

    std::unique_ptr<NodeAST> parseCurrentToken();

    std::unique_ptr<BinaryOperatorNodeAST> parseOperator(std::unique_ptr<NodeAST> lhs);

    std::unique_ptr<NodeAST> parseParentheses();

    std::unique_ptr<NumberNodeAST> parseNumber();

    std::unique_ptr<NodeAST> parseReferenceOrCall();

    bool isCallNode();

    std::unique_ptr<ReferenceNodeAST> parseReference();

    std::unique_ptr<CallNodeAST> parseCall();

    std::unique_ptr<FunctionDefinitionNodeAST> parseFunctionDefinition();

    std::unique_ptr<FunctionPrototypeNodeAST> parseFunctionPrototype();

    bool moveToNextIf(const std::function<bool(Token &)> &predicate);

    void moveToNextToken();

    bool existsNextToken();

    Token &getNextToken();
};

