//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <ostream>
#include <optional>
#include "OperatorDefinition.h"
#include "../Utilities/SourceLocation.h"

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
    std::optional<OperatorDefinition> operatorDefinition;

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        if (token.type != Type::Eof)
            os << "text: \"" << token.text << "\", ";
        os << "offset: " << token.offset
           << ", type: " << toString(token.type);
        if (token.type == Type::Number)
            os << ", numberValue: " << token.numberValue;
        return os;
    }

    [[nodiscard]] inline long getEndOffset() const {
        return offset + (long)text.size();
    }

    [[nodiscard]] inline SourceLocation getSourceLocation() const {
        return SourceLocation(offset, getEndOffset());
    }

    inline static std::string toString(Type type) {
#define returnStr(type) case type: return #type;
        switch (type) {
            returnStr(Eof)
            returnStr(Func)
            returnStr(Identifier)
            returnStr(Number)
            returnStr(Operator)
            returnStr(LeftParenthesis)
            returnStr(RightParenthesis)
            returnStr(LeftBracket)
            returnStr(RightBracket)
            returnStr(Comma)
            returnStr(Semicolon)
        }
    }
};
