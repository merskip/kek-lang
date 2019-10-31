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
        Eof,
        Func,
        Identifier,
        Number,
        Operator,
        LeftParenthesis,
        RightParenthesis,
        LeftBracket,
        RightBracket,
        Comma,
        Semicolon
    } type;
    double numberValue;

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        if (token.type != Type::eof)
            os << "text: \"" << token.text << "\", ";
        os << "offset: " << token.offset
           << ", type: " << toString(token.type);
        if (token.type == Type::number)
            os << ", numberValue: " << token.numberValue;
        return os;
    }

    inline static std::string toString(Type type) {
#define returnStr(type) case type: return #type;
        switch (type) {
            returnStr(eof)
            returnStr(func)
            returnStr(identifier)
            returnStr(number)
            returnStr(binaryOperator)
            returnStr(leftParenthesis)
            returnStr(rightParenthesis)
            returnStr(leftBracket)
            returnStr(rightBracket)
            returnStr(comma)
            returnStr(semicolon)
        }
    }
};
