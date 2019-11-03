//
// Created by Piotr Merski on 03.11.2019.
//

#include "LLVMCompiler.h"
#include "../NodeAST.h"
#include <llvm/Support/raw_ostream.h>


LLVMCompiler::LLVMCompiler(const std::string &moduleId)
        : context(llvm::LLVMContext()),
          module(llvm::Module(moduleId, context)),
          builder(llvm::IRBuilder(context)) {
}

void LLVMCompiler::compile(FileNodeAST *node) {
    enterScope([&] { // Global scope
        node->acceptForValue(this);
    });
    module.print(llvm::outs(), nullptr);
}

llvm::Value *LLVMCompiler::visitForValueBinaryOperatorNode(BinaryOperatorNodeAST *node) {
    auto lhsValue = node->getLhs()->acceptForValue(this);
    auto rhsValue = node->getRhs()->acceptForValue(this);

    if (node->getOperatorText() == "+")
        return builder.CreateFAdd(lhsValue, rhsValue, "add");
    else if (node->getOperatorText() == "-")
        return builder.CreateFSub(lhsValue, rhsValue, "sub");
    else if (node->getOperatorText() == "/")
        return builder.CreateFDiv(lhsValue, rhsValue, "div");
    else if (node->getOperatorText() == "*")
        return builder.CreateFMul(lhsValue, rhsValue, "mul");
    else
        throw "Unknown operator: " + node->getOperatorText();
}

llvm::Value *LLVMCompiler::visitForValueCallNode(CallNodeAST *node) {
    llvm::Function *function = module.getFunction(node->getCallee());
    if (function == nullptr)
        throw "Unknown function: " + node->getCallee();

    if (function->arg_size() != node->getArguments().size())
        throw "Expected " + std::to_string(function->arg_size())
              + " arguments but got " + std::to_string(node->getArguments().size());

    std::vector<llvm::Value *> argumentsValues;
    for (auto &argument: node->getArguments()) {
        auto *argumentCode = argument->acceptForValue(this);
        if (!argumentCode)
            throw "Failed compile argument";
        argumentsValues.push_back(argumentCode);
    }
    return builder.CreateCall(function, argumentsValues, "call");
}

llvm::Value *LLVMCompiler::visitForValueFileNode(FileNodeAST *node) {
    for (auto &childNode : node->getNodes()) {
        childNode->acceptForValue(this);
    }
    return nullptr;
}

llvm::Value *LLVMCompiler::visitForValueFunctionBodyNode(FunctionBodyNodeAST *node) {
    llvm::Value *lastValue = nullptr;
    for (auto &childNode : node->getNodes()) {
        lastValue = childNode->acceptForValue(this);
    }
    return lastValue;
}

llvm::Value *LLVMCompiler::visitForValueFunctionPrototypeNode(FunctionPrototypeNodeAST *node) {
    std::vector<llvm::Type *> argumentsTypes(node->getArguments().size(), llvm::Type::getDoubleTy(context));
    llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(context), argumentsTypes, false);
    llvm::Function *function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, node->getName(), &module);

    int index = 0;
    for (auto &argument: function->args()) {
        auto &argumentName = node->getArguments()[index].get()->getName();
        argument.setName(argumentName);
        index++;
    }
    return function;
}

llvm::Value *LLVMCompiler::visitForValueFunctionDefinitionNode(FunctionDefinitionNodeAST *node) {
    llvm::Function *function = module.getFunction(node->getPrototype()->getName());
    if (function)
        throw "Function " + node->getPrototype()->getName() + " cannot be redefined";
    function = (llvm::Function *)(node->getPrototype()->acceptForValue(this));

    llvm::BasicBlock *implBlock = llvm::BasicBlock::Create(context, "implementation", function);
    builder.SetInsertPoint(implBlock);

    llvm::Value *returnValue;
    enterScope([&] {
        for (auto &arg : function->args()) {
            auto name = arg.getName().str();
            addVariable(name, &arg);
        }
        returnValue = node->getBody()->acceptForValue(this);
    });
    builder.CreateRet(returnValue);
    return function;
}

llvm::Value *LLVMCompiler::visitForValueNumberNode(NumberNodeAST *node) {
    return llvm::ConstantFP::get(context, llvm::APFloat(node->getNumber()));
}

llvm::Value *LLVMCompiler::visitForValueReferenceNode(ReferenceNodeAST *node) {
    return getVariable(node->getName());
}

void LLVMCompiler::enterScope(const std::function<void(void)> &inScope) {
    scopes.emplace_back();
    inScope();
    scopes.pop_back();
}

void LLVMCompiler::addVariable(const std::string &name, llvm::Value *value) {
    scopes.back().addVariable(name, value);
}

llvm::Value *LLVMCompiler::getVariable(const std::string &name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); it++) {
        auto scope = *it;
        auto variable = scope.getVariable(name);
        if (variable != nullptr)
            return variable;
    }
    return nullptr;
}
