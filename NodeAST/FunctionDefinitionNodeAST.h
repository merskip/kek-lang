//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include <llvm/IR/BasicBlock.h>
#include "NodeAST.h"
#include "FunctionPrototypeNodeAST.h"
#include "FunctionBodyNodeAST.h"

struct FunctionDefinitionNodeAST: public NodeAST {

    std::unique_ptr<FunctionPrototypeNodeAST> prototype;
    std::unique_ptr<FunctionBodyNodeAST> body;

    FunctionDefinitionNodeAST(std::unique_ptr<FunctionPrototypeNodeAST> &prototype,
                              std::unique_ptr<FunctionBodyNodeAST> &body,
                              SourceLocation location)
            : prototype(std::move(prototype)), body(std::move(body)), NodeAST(location) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitFunctionDefinitionNode(this);
    }
};

