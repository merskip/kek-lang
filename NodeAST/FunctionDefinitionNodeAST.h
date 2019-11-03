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

    llvm::Value *generateCode(CompileContext *context) const override {
        llvm::Function *function = context->module->getFunction(prototype->getName());
        if (function)
            throw "Function " + prototype->getName() + " cannot be redefined";
        function = prototype->generateFunction(context);

        llvm::BasicBlock *implBlock = llvm::BasicBlock::Create(*context->context, "implementation", function);
        context->builder->SetInsertPoint(implBlock);

        context->enterScope();
        for (auto &arg : function->args()) {
            auto name = arg.getName().str();
            context->addVariable(name, &arg);
        }
        llvm::Value *returnValue = body->generateCode(context);
        context->leaveScope();
        context->builder->CreateRet(returnValue);
        return function;
    }
};

