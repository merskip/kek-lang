//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <string>
#include <vector>
#include <memory>
#include "NodeAST.h"

class CallNodeAST : public NodeAST {

private:
    std::string callee;
    std::vector<std::unique_ptr<NodeAST>> arguments;

public:
    CallNodeAST(std::string &callee, std::vector<std::unique_ptr<NodeAST>> &arguments)
            : callee(callee), arguments(arguments) {
    }

    [[nodiscard]] const std::string &getCallee() const {
        return callee;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<NodeAST>> &getArguments() const {
        return arguments;
    }
};

