//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include <llvm/IR/BasicBlock.h>
#include "NodeAST.h"
#include "FunctionPrototypeNodeAST.h"
#include "FunctionBodyNodeAST.h"

class FunctionDefinitionNodeAST: public NodeAST {

private:
    std::unique_ptr<FunctionPrototypeNodeAST> prototype;
    std::unique_ptr<FunctionBodyNodeAST> body;

public:
    FunctionDefinitionNodeAST(std::unique_ptr<FunctionPrototypeNodeAST> &prototype,
                              std::unique_ptr<FunctionBodyNodeAST> &body)
            : prototype(std::move(prototype)), body(std::move(body)) {
    }

    [[nodiscard]] const std::unique_ptr<FunctionPrototypeNodeAST> &getPrototype() const {
        return prototype;
    }

    [[nodiscard]] const std::unique_ptr<FunctionBodyNodeAST> &getBody() const {
        return body;
    }

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitFunctionDefinitionNode(this);
    }
};

