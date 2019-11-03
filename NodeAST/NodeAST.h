//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <ostream>
#include "../CompileContext.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "../NodeASTVisitor.h"

class NodeAST {

public:
    virtual void accept(NodeASTVisitor *visitor) = 0;

    [[nodiscard]] virtual llvm::Value *generateCode(CompileContext *context) const = 0;
};
