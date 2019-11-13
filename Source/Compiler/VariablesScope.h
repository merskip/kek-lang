//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once


#include <string>
#include <map>
#include <llvm/IR/Value.h>

class VariablesScope {
private:
    std::map<std::string, llvm::Value *> variables;

public:
    void addVariable(const std::string &name, llvm::Value *value);

    llvm::Value *getVariable(const std::string &name);
};
