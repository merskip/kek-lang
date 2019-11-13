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
};

