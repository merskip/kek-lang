//
// Created by Piotr Merski on 02.11.2019.
//

#pragma once

#include <list>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class VariablesScope {
private:
    std::map<std::string, llvm::Value *> variables;

public:
    void addVariable(std::string &name, llvm::Value *value) {
        variables[name] = value;
    }

    llvm::Value *getVariable(const std::string &name) {
        return variables[name];
    }
};

class CompileContext {

private:
    std::list<VariablesScope> scopes;

public:
    llvm::LLVMContext *context;
    llvm::Module *module;
    llvm::IRBuilder<> *builder;

    CompileContext(llvm::LLVMContext *context, llvm::Module *module, llvm::IRBuilder<> *builder)
            : context(context),
              module(module),
              builder(builder) {
    }

    void enterScope() {
        scopes.emplace_back();
    }

    void addVariable(std::string &name, llvm::Value *value) {
        scopes.back().addVariable(name, value);
    }

    llvm::Value *getVariable(const std::string &name) {
        for (auto &scope : scopes) {
            auto value = scope.getVariable(name);
            if (value != nullptr)
                return value;
        }
        return nullptr;
    }

    void leaveScope() {
        scopes.pop_back();
    }
};

