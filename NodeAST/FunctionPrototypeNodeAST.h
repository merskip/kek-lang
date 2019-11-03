//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include "NodeAST.h"
#include <string>
#include <vector>
#include "ReferenceNodeAST.h"

struct FunctionPrototypeNodeAST : public NodeAST {

    std::string name;
    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;

    FunctionPrototypeNodeAST(std::string &name, std::vector<std::unique_ptr<ReferenceNodeAST>> &arguments)
            : name(name), arguments(std::move(arguments)) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitFunctionPrototypeNode(this);
    }
};

