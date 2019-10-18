//
// Created by Piotr Merski on 18.10.2019.
//

#include <stdexcept>
#include "Tokenizer.h"

std::list<Token> Tokenizer::getTokens() {
    std::list<Token> tokens;
    while (true) {
        Token token = getNextToken();
        tokens.push_back(token);

        if (token.type == Token::Type::eof)
            break;
    }
    return tokens;
}

Token Tokenizer::getNextToken() {
    char currentChar = getNextChar();

    // Skip whitespaces
    while (isspace(currentChar))
        currentChar = getNextChar();

    if (isalpha(currentChar)) { // [a-Z][a-Z0-9]*
        std::string identifierText;

        do {
            identifierText += currentChar;
        } while (isalnum(currentChar = getNextChar()));

        if (identifierText == "func") {
            return createToken(identifierText, Token::Type::func);
        } else {
            return createToken(identifierText, Token::Type::identifier);
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

        } while (isdigit(currentChar = getNextChar()) || currentChar == '.');

        return createToken(numberText, Token::Type::number, std::stod(numberText));
    } else if (currentChar == '#') {
        do {
            currentChar = getNextChar();
        } while (currentChar != EOF && currentChar != '\r' && currentChar != '\n');

        return getNextToken();
    } else if (currentChar == EOF || currentChar == '\0' || currentChar == '\177') {
        std::string tempText(1, currentChar);
        return createToken(tempText, Token::Type::eof);
    } else {
        throw std::invalid_argument("Unexpected " + std::string(1, currentChar));
    }
}

Token Tokenizer::createToken(std::string &tokenText, Token::Type type, double numberValue) {
    return Token{
            .text = tokenText,
            .offset = currentOffset - (long) tokenText.size(),
            .type = type,
            numberValue = numberValue
    };
}

char Tokenizer::getNextChar() {
    currentOffset++;
    return this->text[currentOffset];
}
