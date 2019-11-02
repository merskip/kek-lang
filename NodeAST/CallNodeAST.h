//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/IRBuilder.h>
#include "NodeAST.h"

class CallNodeAST : public NodeAST {

private:
    std::string callee;
    std::vector<std::unique_ptr<NodeAST>> arguments;

public:
    CallNodeAST(std::string &callee, std::vector<std::unique_ptr<NodeAST>> &arguments)
            : callee(callee), arguments(std::move(arguments)) {
    }

    [[nodiscard]] const std::string &getCallee() const {
        return callee;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<NodeAST>> &getArguments() const {
        return arguments;
    }

    llvm::Value *generateCode(CompileContext *context) const override {
        llvm::Function *function = context->module->getFunction(callee);
        if (function == nullptr)
            throw "Unknown function: " + callee;

        if (function->arg_size() != arguments.size())
            throw "Expected " + std::to_string(function->arg_size())
                  + " arguments but got " + std::to_string(arguments.size());

        std::vector<llvm::Value *> argumentsValues;
        for (auto &argument: arguments) {
            auto *argumentCode = argument->generateCode(context);
            if (!argumentCode)
                throw "Failed compile argument";
            argumentsValues.push_back(argumentCode);
        }
        return context->builder->CreateCall(function, argumentsValues, "call");
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("CallNodeAST", {
                {"callee", callee},
        });
        for (auto &argument : arguments) {
            printer.printChildNode(*argument, "Argument");
        }
    }
};

