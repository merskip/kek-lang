//
// Created by Piotr Merski on 14.11.2019.
//

#pragma once

#include <gtest/gtest.h>
#include <list>
#include <Lexer/Token.h>

#define ARGS_SIZE(array) (sizeof(array)/sizeof(array[0]))
#define ARGS_POINTER(array) ((char **)(array))

::testing::AssertionResult checkTokens(std::list<Token> &tokens, std::vector<Token::Type> expectedTypes);

