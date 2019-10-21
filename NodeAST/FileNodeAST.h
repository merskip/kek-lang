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

    llvm::Value *generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const override {
        for (auto &node : nodes) {
            auto *code = node->generateCode(context, module, builder);
        }
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("FileNodeAST");
        for (auto &node : nodes) {
            printer.printChildNode(*node);
        }
    }
};

