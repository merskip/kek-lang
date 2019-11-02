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

    llvm::Value *generateCode(CompileContext *context) const override {
        llvm::Value *lastCode = nullptr;
        for (auto &node : nodes) {
            lastCode = node->generateCode(context);
        }
        return lastCode;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("FunctionBodyNodeAST");
        for (auto &node : nodes) {
            printer.printChildNode(*node);
        }
    }
};

