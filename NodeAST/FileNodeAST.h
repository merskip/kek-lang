//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once


#include <utility>
#include <vector>
#include <memory>
#include "NodeAST.h"

struct FileNodeAST : public NodeAST {

    std::vector<std::unique_ptr<NodeAST>> nodes;

    FileNodeAST(std::vector<std::unique_ptr<NodeAST>> &nodes)
            : nodes(std::move(nodes)) {
    }

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitFileNode(this);
    }
};
