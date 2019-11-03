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

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitNumberNode(this);
    }
};
