//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <cmath>
#include <list>
#include "Token.h"

class Tokenizer {

private:
    const std::string &text;
    long currentOffset = -1;

public:
    explicit Tokenizer(const std::string &text)
            : text(text) {
    }

    std::list<Token> getTokens();

    Token getNextToken();

private:
    Token createToken(std::string &tokenText, Token::Type type, double numberValue = NAN);

    char getNextCharOrEOF();

    void backToPreviousChar();
};
