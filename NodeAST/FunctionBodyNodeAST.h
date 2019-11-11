//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once


#include <memory>
#include <utility>
#include "NodeAST.h"

struct FunctionBodyNodeAST : public NodeAST {

    std::vector<std::unique_ptr<NodeAST>> nodes;

    FunctionBodyNodeAST(std::vector<std::unique_ptr<NodeAST>> &nodes, SourceLocation location)
            : nodes(std::move(nodes)), NodeAST(location) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitFunctionBodyNode(this);
    }
};

