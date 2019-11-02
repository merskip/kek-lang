//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include "NodeAST.h"
#include <string>
#include <vector>

class FunctionPrototypeNodeAST : public NodeAST {

private:
    std::string name;
    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;

public:
    FunctionPrototypeNodeAST(std::string &name, std::vector<std::unique_ptr<ReferenceNodeAST>> &arguments)
            : name(name), arguments(std::move(arguments)) {
    }

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<ReferenceNodeAST>> &getArguments() const {
        return arguments;
    }

    llvm::Value *generateCode(CompileContext *context) const override {
        return generateFunction(context);
    }

    llvm::Function *generateFunction(CompileContext *context) const {
        std::vector<llvm::Type *> argumentsTypes(arguments.size(), llvm::Type::getDoubleTy(*context->context));
        llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(*context->context), argumentsTypes, false);
        llvm::Function *function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, context->module);

        int index = 0;
        for (auto &argument: function->args()) {
            auto &argumentName = arguments[index].get()->getName();
            argument.setName(argumentName);
            index++;
        }
        return function;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("FunctionPrototypeNodeAST", {
                {"name", name}
        });
        for (auto &argument : arguments) {
            printer.printChildNode(*argument, "Argument");
        }
    }
};

