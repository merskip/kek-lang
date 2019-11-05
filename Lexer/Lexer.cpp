//
// Created by Piotr Merski on 18.10.2019.
//

#include <algorithm>
#include "Lexer.h"
#include "../ParsingException.h"

std::list<Token> Lexer::getTokens() {
    std::list<Token> tokens;
    while (true) {
        Token token = getNextToken();
        tokens.push_back(token);

        if (token.type == Token::Type::Eof)
            break;
    }
    return tokens;
}

Token Lexer::getNextToken() {
    char currentChar = getNextCharOrEOF();

    // Skip whitespaces
    while (isspace(currentChar))
        currentChar = getNextCharOrEOF();
    std::string currentCharStr(1, currentChar);

    if (isalpha(currentChar)) { // [a-Z][a-Z0-9]*
        std::string identifierText;

        do {
            identifierText += currentChar;
        } while (isalnum(currentChar = getNextCharOrEOF()));
        backToPreviousChar();

        if (identifierText == "func") {
            return createToken(identifierText, Token::Type::Func);
        } else {
            return createToken(identifierText, Token::Type::Identifier);
        }
    } else if (isdigit(currentChar)) { // [0-9]+
        std::string numberText;
        bool visitedSeparator = false;

        do {
            numberText += currentChar;
            if (currentChar == '.') {
                if (visitedSeparator)
                    throw std::invalid_argument("Unexpected " + std::string(1, currentChar));
                visitedSeparator = true;
            }

        } while (isdigit(currentChar = getNextCharOrEOF()) || currentChar == '.');
        backToPreviousChar();

        return createTokenNumber(numberText, std::stod(numberText));
    } else if (currentChar == '#') {
        do {
            currentChar = getNextCharOrEOF();
        } while (currentChar != EOF && currentChar != '\r' && currentChar != '\n');

        return getNextToken();
    } else if (currentChar == '(') {
        return createToken(currentCharStr, Token::Type::LeftParenthesis);
    } else if (currentChar == ')') {
        return createToken(currentCharStr, Token::Type::RightParenthesis);
    } else if (currentChar == '{') {
        return createToken(currentCharStr, Token::Type::LeftBracket);
    } else if (currentChar == '}') {
        return createToken(currentCharStr, Token::Type::RightBracket);
    } else if (currentChar == ',') {
        return createToken(currentCharStr, Token::Type::Comma);
    } else if (currentChar == ';') {
        return createToken(currentCharStr, Token::Type::Semicolon);
    } else if (currentChar == EOF) {
        return createToken(currentCharStr, Token::Type::Eof);
    }

    auto operatorDefinition = findOperator(currentCharStr);
    if (operatorDefinition.has_value()) {
        return createTokenOperator(currentCharStr, *operatorDefinition);
    } else {
        throw ParsingException(currentOffset, "Unexpected " + std::string(1, currentChar));
    }
}

Token Lexer::createToken(std::string &tokenText, Token::Type type) {
    return Token{
            .text = tokenText,
            .offset = currentOffset - (long) tokenText.size() + 1,
            .type = type,
            .numberValue = NAN,
            .operatorDefinition = std::nullopt
    };
}

Token Lexer::createTokenNumber(std::string &tokenText, double numberValue) {
    return Token{
            .text = tokenText,
            .offset = currentOffset - (long) tokenText.size() + 1,
            .type = Token::Type::Number,
            .numberValue = numberValue,
            .operatorDefinition = std::nullopt
    };
}

Token Lexer::createTokenOperator(std::string &tokenText, const OperatorDefinition &operatorDefinition) {
    return Token{
            .text = tokenText,
            .offset = currentOffset - (long) tokenText.size() + 1,
            .type = Token::Type::Operator,
            .numberValue = NAN,
            .operatorDefinition = operatorDefinition
    };
}

char Lexer::getNextCharOrEOF() {
    currentOffset++;
    if (currentOffset < this->text.size())
        return this->text[currentOffset];
    else
        return EOF;
}

void Lexer::backToPreviousChar() {
    currentOffset--;
}

std::optional<OperatorDefinition> Lexer::findOperator(const std::string &symbol) {
    for (const auto &op : operators) {
        if (op.symbol == symbol)
            return op;
    }
    return std::nullopt;
}
