//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once

#include <list>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "../NodeAST/FileNodeAST.h"
#include "VariablesScope.h"

class LLVMCompiler: public NodeASTValueVisitor<llvm::Value *> {

private:
    llvm::LLVMContext context;
    llvm::Module module;
    llvm::IRBuilder<> builder;

    std::list<VariablesScope> scopes;

public:
    explicit LLVMCompiler(const std::string &moduleId);

    void compile(FileNodeAST *node);

private:
    llvm::Value *visitForValueBinaryOperatorNode(const BinaryOperatorNodeAST *node) override;
    llvm::Value *visitForValueCallNode(const CallNodeAST *node) override;
    llvm::Value *visitForValueFileNode(const FileNodeAST *node) override;
    llvm::Value *visitForValueFunctionBodyNode(const FunctionBodyNodeAST *node) override;
    llvm::Value *visitForValueFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) override;
    llvm::Value *visitForValueFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) override;
    llvm::Value *visitForValueNumberNode(const NumberNodeAST *node) override;
    llvm::Value *visitForValueReferenceNode(const ReferenceNodeAST *node) override;

    void enterScope(const std::function<void(void)> &inScope);
    void addVariable(const std::string &name, llvm::Value *value);
    llvm::Value *getVariable(const std::string &name);
};

