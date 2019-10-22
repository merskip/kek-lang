//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <list>
#include <memory>
#include "Token.h"
#include "NodeAST/NodeAST.h"
#include "NodeAST/NumberNodeAST.h"
#include "NodeAST/ReferenceNodeAST.h"
#include "NodeAST/CallNodeAST.h"
#include "NodeAST/FunctionDefinitionNodeAST.h"
#include "NodeAST/FileNodeAST.h"

class NodeASTParser {

private:
    std::list<Token> tokens;
    long currentOffset = -1;
    Token &currentToken;

public:
    explicit NodeASTParser(std::list<Token> &tokens)
            : tokens(tokens), currentToken(*tokens.begin()) {
    }

    std::unique_ptr<FileNodeAST> parse();

private:

    std::unique_ptr<NodeAST> parseToken();

    std::unique_ptr<NodeAST> parseParentheses();

    std::unique_ptr<NumberNodeAST> parseNumber();

    std::unique_ptr<NodeAST> parseReferenceOrCall();

    bool isCallNode();

    std::unique_ptr<ReferenceNodeAST> parseReference();

    std::unique_ptr<CallNodeAST> parseCall();

    std::unique_ptr<FunctionDefinitionNodeAST> parseFunctionDefinition();

    std::unique_ptr<FunctionPrototypeNodeAST> parseFunctionPrototype();

    void moveToNextToken();

    bool existsNextToken();

    Token &getNextToken();
};

