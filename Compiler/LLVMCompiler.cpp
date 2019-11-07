//
// Created by Piotr Merski on 03.11.2019.
//

#include "LLVMCompiler.h"
#include "../NodeAST/all.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/CodeGen/CommandFlags.inc>
#include <llvm/CodeGen/MachineModuleInfo.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Verifier.h>
#include <iostream>

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

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    module.setTargetTriple(targetTriple);
    std::string err;
    auto target = TargetRegistry::lookupTarget(targetTriple, err);


    TargetOptions opt;
    auto relocModel = Optional<Reloc::Model>();
    auto targetMachine = target->createTargetMachine(module.getTargetTriple(), "generic", "", opt, relocModel);
    module.setDataLayout(targetMachine->createDataLayout());

    std::error_code errFile;
    std::unique_ptr<llvm::ToolOutputFile> outputFile = std::make_unique<ToolOutputFile>("kek.o", errFile, sys::fs::OF_Text);
    raw_pwrite_stream *outputStream = &outputFile->os();

    legacy::PassManager pass;
    targetMachine->addPassesToEmitFile(pass, *outputStream, nullptr, TargetMachine::CGFT_ObjectFile);
    pass.run(module);
    outputStream->flush();
    outputFile->keep();
}

llvm::Value *LLVMCompiler::visitForValueBinaryOperatorNode(const BinaryOperatorNodeAST *node) {
    auto lhsValue = node->lhs->acceptForValue(this);
    auto rhsValue = node->rhs->acceptForValue(this);

    if (node->operatorText == "+")
        return builder.CreateFAdd(lhsValue, rhsValue, "add");
    else if (node->operatorText == "-")
        return builder.CreateFSub(lhsValue, rhsValue, "sub");
    else if (node->operatorText == "/")
        return builder.CreateFDiv(lhsValue, rhsValue, "div");
    else if (node->operatorText == "*")
        return builder.CreateFMul(lhsValue, rhsValue, "mul");
    else
        throw "Unknown operator: " + node->operatorText;
}

llvm::Value *LLVMCompiler::visitForValueCallNode(const CallNodeAST *node) {
    llvm::Function *function = module.getFunction(node->callee);
    if (function == nullptr)
        throw "Unknown function: " + node->callee;

    if (function->arg_size() != node->arguments.size())
        throw "Expected " + std::to_string(function->arg_size())
              + " arguments but got " + std::to_string(node->arguments.size());

    std::vector<llvm::Value *> argumentsValues;
    for (auto &argument: node->arguments) {
        auto *argumentCode = argument->acceptForValue(this);
        if (!argumentCode)
            throw "Failed compile argument";
        argumentsValues.push_back(argumentCode);
    }
    return builder.CreateCall(function, argumentsValues, "call");
}

llvm::Value *LLVMCompiler::visitForValueFileNode(const FileNodeAST *node) {
    for (auto &childNode : node->nodes) {
        childNode->acceptForValue(this);
    }
    return nullptr;
}

llvm::Value *LLVMCompiler::visitForValueFunctionBodyNode(const FunctionBodyNodeAST *node) {
    llvm::Value *lastValue = nullptr;
    for (auto &childNode : node->nodes) {
        lastValue = childNode->acceptForValue(this);
    }
    return lastValue;
}

llvm::Value *LLVMCompiler::visitForValueFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) {
    std::vector<llvm::Type *> argumentsTypes(node->arguments.size(), llvm::Type::getDoubleTy(context));
    llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(context), argumentsTypes, false);
    llvm::Function *function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, node->name, &module);

    int index = 0;
    for (auto &argument: function->args()) {
        auto &argumentName = node->arguments[index].get()->name;
        argument.setName(argumentName);
        index++;
    }
    return function;
}

llvm::Value *LLVMCompiler::visitForValueFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) {
    llvm::Function *function = module.getFunction(node->prototype->name);
    if (function)
        throw "Function " + node->prototype->name + " cannot be redefined";
    function = (llvm::Function *)(node->prototype->acceptForValue(this));

    llvm::BasicBlock *implBlock = llvm::BasicBlock::Create(context, "implementation", function);
    builder.SetInsertPoint(implBlock);

    llvm::Value *returnValue;
    enterScope([&] {
        for (auto &arg : function->args()) {
            auto name = arg.getName().str();
            addVariable(name, &arg);
        }
        returnValue = node->body->acceptForValue(this);
    });
    builder.CreateRet(returnValue);
    return function;
}

llvm::Value *LLVMCompiler::visitForValueNumberNode(const NumberNodeAST *node) {
    return llvm::ConstantFP::get(context, llvm::APFloat(node->number));
}

llvm::Value *LLVMCompiler::visitForValueReferenceNode(const ReferenceNodeAST *node) {
    return getVariable(node->name);
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
