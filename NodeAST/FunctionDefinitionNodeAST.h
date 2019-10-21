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

    llvm::Value *generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const override {
        llvm::Function *function = module->getFunction(prototype->getName());
        if (function)
            throw "Function " + prototype->getName() + " cannot be redefined";
        function = prototype->generateFunction(context, module, builder);

        llvm::BasicBlock *implBlock = llvm::BasicBlock::Create(*context, "implementation", function);
        builder->SetInsertPoint(implBlock);

        llvm::Value *returnValue = body->generateCode(context, module, builder);
        builder->CreateRet(returnValue);
        return function;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("FunctionDefinitionNodeAST");
        printer.printChildNode(*prototype, "Prototype");
        printer.printChildNode(*body, "Body");
    }
};

