//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once


#include <utility>
#include <vector>
#include <memory>
#include "NodeAST.h"

class FileNodeAST : public NodeAST {

private:
    std::vector<std::unique_ptr<NodeAST>> nodes;

public:
    explicit FileNodeAST(std::vector<std::unique_ptr<NodeAST>> &nodes)
            : nodes(std::move(nodes)) {
    }

    [[nodiscard]] const std::vector<std::unique_ptr<NodeAST>> &getNodes() const {
        return nodes;
    }

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitFileNode(this);
    }
};

