//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <cmath>
#include <list>
#include <vector>
#include "Token.h"

class Lexer {

private:
    const std::string &text;
    long currentOffset = -1;
    std::vector<char> operators;

public:
    explicit Lexer(const std::string &text)
            : text(text) {
        addOperator('+');
        addOperator('-');
        addOperator('/');
        addOperator('*');
    }

    void addOperator(char op) {
        operators.push_back(op);
    }

    std::list<Token> getTokens();

private:
    Token getNextToken();

    Token createToken(std::string &tokenText, Token::Type type, double numberValue = NAN);

    char getNextCharOrEOF();

    void backToPreviousChar();

    bool containsOperator(char op);
};