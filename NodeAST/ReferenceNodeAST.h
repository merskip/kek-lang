//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include "NodeAST.h"

class ReferenceNodeAST: public NodeAST {

private:
    std::string name;

public:
    explicit ReferenceNodeAST(std::string &name) : name(name) {
    }

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    llvm::Value *generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const override {
        return nullptr;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("ReferenceNodeAST", {
                {"name", name}
        });
    }
};

