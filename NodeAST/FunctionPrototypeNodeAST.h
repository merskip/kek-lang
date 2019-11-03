//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include "NodeAST.h"
#include <string>
#include <vector>
#include "ReferenceNodeAST.h"

class FunctionPrototypeNodeAST : public NodeAST {

private:
    std::string name;
    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;

public:
    FunctionPrototypeNodeAST(std::string &name, std::vector<std::unique_ptr<ReferenceNodeAST>> &arguments)
            : name(name), arguments(std::move(arguments)) {
    }

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<ReferenceNodeAST>> &getArguments() const {
        return arguments;
    }

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitFunctionPrototypeNode(this);
    }
};

