//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/IRBuilder.h>
#include "NodeAST.h"

struct CallNodeAST : public NodeAST {

    std::string callee;
    std::vector<std::unique_ptr<NodeAST>> arguments;

    CallNodeAST(std::string &callee, std::vector<std::unique_ptr<NodeAST>> &arguments)
            : callee(callee), arguments(std::move(arguments)) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitCallNode(this);
    }
};

