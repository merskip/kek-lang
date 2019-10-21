//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include "NodeAST.h"

class NumberNodeAST : public NodeAST {

private:
    double number;

public:
    explicit NumberNodeAST(double number) : number(number) {}

    [[nodiscard]] double getNumber() const {
        return number;
    }

    [[nodiscard]] llvm::Value *
    generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const override {
        return llvm::ConstantFP::get(*context, llvm::APFloat(number));
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("NumberNodeAST", {
                {"value", std::to_string(number)}
        });
    }
};
