//
// Created by Piotr Merski on 16.11.2019.
//

#include <gtest/gtest.h>
#include <Utilities/Arguments.h>
#include "TestUtilities.h"

TEST(ArgumentsTests, givenOneFlag_returnsIsFlag) {
    char const *args[1] = {"-flag"};
    arguments.initialize(ARGS_SIZE(args), ARGS_POINTER(args));

    EXPECT_TRUE(arguments.isFlag("-flag"));
    EXPECT_EQ(arguments.getOption("-flag"), std::nullopt);
}

TEST(ArgumentsTests, givenOptionWithoutValue_returnsNull) {
    char const *args[1] = {"-option"};
    arguments.initialize(ARGS_SIZE(args), ARGS_POINTER(args));

    EXPECT_TRUE(arguments.isFlag("-option")); // Any option could be use a flag
    EXPECT_EQ(arguments.getOption("-option"), std::nullopt);
}

TEST(ArgumentsTests, givenNoOption_returnsNull) {
    char const *args[1] = {"-another-option-or-flag"};
    arguments.initialize(ARGS_SIZE(args), ARGS_POINTER(args));

    EXPECT_FALSE(arguments.isFlag("-option"));
    EXPECT_EQ(arguments.getOption("-option"), std::nullopt);
}

TEST(ArgumentsTests, givenOption_returnsValue) {
    char const *args[2] = {"-option", "2"};
    arguments.initialize(ARGS_SIZE(args), ARGS_POINTER(args));

    EXPECT_TRUE(arguments.isFlag("-option"));
    EXPECT_EQ(arguments.getOption("-option").value(), "2");
}

TEST(ArgumentsTests, givenFlagAndOption_returnsIsFlagAndValueForOption) {
    char const *args[3] = {"-flag", "-option", "2"};
    arguments.initialize(ARGS_SIZE(args), ARGS_POINTER(args));

    EXPECT_TRUE(arguments.isFlag("-flag"));
    EXPECT_TRUE(arguments.isFlag("-option"));
    EXPECT_EQ(arguments.getOption("-option").value(), "2");
}
