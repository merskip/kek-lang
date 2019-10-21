//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <ostream>
#include "../NodeASTPrinter.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class NodeAST {

public:
    [[nodiscard]] virtual llvm::Value *generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const = 0;

    virtual void print(NodeASTPrinter &printer) const = 0;
};
