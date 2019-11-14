//
// Created by Piotr Merski on 13.11.2019.
//

#include <gtest/gtest.h>
#include "Lexer/Lexer.h"
#include "TestUtils.h"

TEST(LexerTests, givenOneSymbol_returnsTwoTokens) {
    auto lexer = Lexer("d", {});

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Identifier, Token::Type::Eof
    }));
}

TEST(LexerTests, givenTwoSymbol_returnsThreeToken) {
    auto lexer = Lexer("d 2", {});

    auto tokens = lexer.getTokens();

    EXPECT_TRUE(checkTokens(tokens, {
            Token::Type::Identifier, Token::Type::Number, Token::Type::Eof
    }));
}