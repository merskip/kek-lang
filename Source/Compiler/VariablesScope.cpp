//
// Created by Piotr Merski on 03.11.2019.
//

#include "VariablesScope.h"

void VariablesScope::addVariable(const std::string &name, llvm::Value *value) {
    variables[name] = value;
}

llvm::Value *VariablesScope::getVariable(const std::string &name) {
    return variables[name];
}
