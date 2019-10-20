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
        number,
        leftParenthesis,
        rightParenthesis,
        leftBracket,
        rightBracket,
        comma,
        semicolon
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
        switch (type) {
            case eof:
                return "eof";
            case func:
                return "func";
            case identifier:
                return "identifier";
            case number:
                return "number";
            case leftParenthesis:
                return "leftParenthesis";
            case rightParenthesis:
                return "rightParenthesis";
            case leftBracket:
                return "leftBracket";
            case rightBracket:
                return "rightBracket";
            case comma:
                return "comma";
            case semicolon:
                return "semicolon";
        }
    }
};
