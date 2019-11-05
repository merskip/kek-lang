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
    const std::string &text;
    long currentOffset = -1;
    const std::vector<OperatorDefinition> &operators;

public:
    explicit Lexer(const std::string &text, const std::vector<OperatorDefinition> &operators)
            : text(text), operators(operators) {
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
