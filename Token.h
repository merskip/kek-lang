//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <ostream>

struct Token {
    std::string text;
    long offset;
    enum Type {
        eof,
        func,
        identifier,
        number
    } type;
    double numberValue;

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "text: \"" << token.text << "\""
           << ", offset: " << token.offset
           << ", type: " << token.type
           << ", numberValue: " << token.numberValue;
        return os;
    }
};
