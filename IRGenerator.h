//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include "NodeAST/FileNodeAST.h"

class IRGenerator {

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
    std::map<std::string, llvm::Value *> namedValues;

public:
    IRGenerator()
            : context(llvm::LLVMContext()),
              builder(llvm::IRBuilder(context)),
              module(llvm::Module("kek-lang", context)) {
    }


    void run(std::unique_ptr<FileNodeAST> fileNode);

};
