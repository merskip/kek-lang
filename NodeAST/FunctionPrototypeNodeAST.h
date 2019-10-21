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

    llvm::Value *generateCode(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const override {
        return generateFunction(context, module, builder);
    }

    llvm::Function *generateFunction(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder) const {
        std::vector<llvm::Type *> argumentsTypes(arguments.size(), llvm::Type::getDoubleTy(*context));
        llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(*context), argumentsTypes, false);
        llvm::Function *function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, name, module);

        int index = 0;
        for (auto &argument: function->args()) {
            argument.setName(arguments[index].get()->getName());
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

