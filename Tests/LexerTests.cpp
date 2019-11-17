//
// Created by Piotr Merski on 13.11.2019.
//

#include <gtest/gtest.h>
#include <BuiltinTypes.h>
#include <Utilities/ParsingException.h>
#include "Lexer/Lexer.h"
#include "TestUtilities.h"

TEST(LexerTests, givenOneSymbol_returnsTwoTokens) {
    auto lexer = Lexer("d", {});

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Identifier, Token::Type::Eof
    }));
}

TEST(LexerTests, givenAllKnownSymbols_returnsAllKnownSymbols) {
    auto lexer = Lexer("func abc 10 + ( ) { } , ;", builtin::operators);

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Func,
            Token::Type::Identifier,
            Token::Type::Number,
            Token::Type::Operator,
            Token::Type::LeftParenthesis,
            Token::Type::RightParenthesis,
            Token::Type::LeftBracket,
            Token::Type::RightBracket,
            Token::Type::Comma,
            Token::Type::Semicolon,
            Token::Type::Eof,
    }));
}

TEST(LexerTests, givenDecimalNumber_returnsSingleToken) {
    auto lexer = Lexer("1.23", builtin::operators);

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Number,
            Token::Type::Eof,
    }));

    EXPECT_EQ(tokens.front().numberValue, 1.23);
}

TEST(LexerTests, givenKnownOperator_returnsOperator) {
    auto operatorDefinition = OperatorDefinition("+", 100);
    auto lexer = Lexer("+", {operatorDefinition});

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Operator,
            Token::Type::Eof,
    }));

    EXPECT_EQ(tokens.front().operatorDefinition, operatorDefinition);
}

TEST(LexerTests, givenUnknownToken_throwsException) {
    auto lexer = Lexer("%", {});

    EXPECT_THROW(lexer.getTokens(), ParsingException);
}

TEST(LexerTests, givenNumberWithTwoDots_throwsException) {
    auto lexer = Lexer("12.3.4", {});

    EXPECT_THROW(lexer.getTokens(), ParsingException);
}

TEST(LexerTests, givenTextWithComment_returnsTokenUntilComment) {
    auto lexer = Lexer("a # b", {});

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Identifier,
            Token::Type::Eof,
    }));
}

TEST(LexerTests, tokenToString_returnsName) {
    EXPECT_EQ(Token::toString(Token::Type::Eof), "Eof");
    EXPECT_EQ(Token::toString(Token::Type::Func), "Func");
    EXPECT_EQ(Token::toString(Token::Type::Identifier), "Identifier");
    EXPECT_EQ(Token::toString(Token::Type::Number), "Number");
    EXPECT_EQ(Token::toString(Token::Type::Operator), "Operator");
    EXPECT_EQ(Token::toString(Token::Type::LeftParenthesis), "LeftParenthesis");
    EXPECT_EQ(Token::toString(Token::Type::RightParenthesis), "RightParenthesis");
    EXPECT_EQ(Token::toString(Token::Type::LeftBracket), "LeftBracket");
    EXPECT_EQ(Token::toString(Token::Type::RightBracket), "RightBracket");
    EXPECT_EQ(Token::toString(Token::Type::Comma), "Comma");
    EXPECT_EQ(Token::toString(Token::Type::Semicolon), "Semicolon");
}
