//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <cmath>
#include <list>
#include <utility>
#include <vector>
#include "Token.h"

class Lexer {

private:
    std::string text;
    long currentOffset = -1;
    std::vector<OperatorDefinition> operators;

public:
    explicit Lexer(std::string text, std::vector<OperatorDefinition> operators)
            : text(std::move(text)), operators(std::move(operators)) {
    }

    std::list<Token> getTokens();

private:
    Token getNextToken();

    Token createToken(std::string &tokenText, Token::Type type);

    Token createTokenNumber(std::string &tokenText, double numberValue);

    Token createTokenOperator(std::string &tokenText, const OperatorDefinition &operatorDefinition);

    char getNextCharOrEOF();

    void backToPreviousChar();

    std::optional<OperatorDefinition> findOperator(const std::string &symbol);
};
