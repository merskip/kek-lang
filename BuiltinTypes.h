//
// Created by Piotr Merski on 04.11.2019.
//

#pragma once

#include <list>
#include "Lexer/OperatorDefinition.h"

namespace builtin {

    const static std::vector<OperatorDefinition> operators = {
            OperatorDefinition("+", 100),
            OperatorDefinition("-", 100),
            OperatorDefinition("*", 200),
            OperatorDefinition("/", 200)
    };
}
