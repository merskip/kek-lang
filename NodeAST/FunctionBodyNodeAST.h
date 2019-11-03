//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once


#include <memory>
#include <utility>
#include "NodeAST.h"

class FunctionBodyNodeAST : public NodeAST {

private:
    std::vector<std::unique_ptr<NodeAST>> nodes;

public:
    explicit FunctionBodyNodeAST(std::vector<std::unique_ptr<NodeAST>> &nodes)
            : nodes(std::move(nodes)) {
    }

    [[nodiscard]] const std::vector<std::unique_ptr<NodeAST>> &getNodes() const {
        return nodes;
    }

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitFunctionBodyNode(this);
    }
};

