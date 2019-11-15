//
// Created by Piotr Merski on 04.11.2019.
//

#pragma once


#include <string>
#include <utility>

struct OperatorDefinition {

    std::string symbol;
    int precedence;

    OperatorDefinition(std::string symbol, int precedence)
            : symbol(std::move(symbol)), precedence(precedence) {
    }

    bool operator==(const OperatorDefinition &rhs) const {
        return symbol == rhs.symbol &&
               precedence == rhs.precedence;
    }

    bool operator!=(const OperatorDefinition &rhs) const {
        return !(rhs == *this);
    }
};

