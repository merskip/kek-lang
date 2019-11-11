//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include "NodeAST.h"

struct NumberNodeAST : public NodeAST {

    double number;

    NumberNodeAST(double number, SourceLocation location) : number(number), NodeAST(location) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitNumberNode(this);
    }
};
