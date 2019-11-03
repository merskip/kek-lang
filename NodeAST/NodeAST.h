//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <ostream>
#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "../Utilities/NodeASTVisitor.h"
#include "../Utilities/NodeASTValueVisitor.h"

struct NodeAST {

    virtual void accept(NodeASTVisitor *visitor) const = 0;

    template<typename ReturnValue>
    ReturnValue acceptForValue(NodeASTValueVisitor<ReturnValue> *valueVisitor) const {
        accept(valueVisitor);
        return valueVisitor->getValue();
    }
};
