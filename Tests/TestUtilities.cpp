//
// Created by Piotr Merski on 17.11.2019.
//

#include "TestUtilities.h"

::testing::AssertionResult checkTokens(std::list<Token> &tokens, std::vector<Token::Type> expectedTypes) {
    if (tokens.size() != expectedTypes.size())
        return ::testing::AssertionFailure() << "Expected " << expectedTypes.size() << " tokens, but got " << tokens.size();

    for (std::size_t i = 0; i < tokens.size(); i++) {
        auto token = std::next(tokens.begin(), i);
        auto expectedType = expectedTypes[i];
        if (token->type != expectedType)
            return ::testing::AssertionFailure() << "Expected '" << Token::toString(expectedType) << "' type, but got '"
                                                 << Token::toString(token->type) << "' type at " << i << " index";
    }
    return ::testing::AssertionSuccess();
}