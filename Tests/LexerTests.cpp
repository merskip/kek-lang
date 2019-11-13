//
// Created by Piotr Merski on 13.11.2019.
//

#include <gtest/gtest.h>
#include "Lexer/Lexer.h"

TEST(LexerTests, givenOneSymbol_returnsTwoTokens) {
    auto lexer = Lexer("d", {});

    auto tokens = lexer.getTokens();

    EXPECT_EQ(tokens.size(), 2);
}

TEST(LexerTests, givenTwoSymbol_returnsThreeToken) {
    auto lexer = Lexer("d 2", {});

    auto tokens = lexer.getTokens();

    EXPECT_EQ(tokens.size(), 3);
}