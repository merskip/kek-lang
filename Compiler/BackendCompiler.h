//
// Created by Piotr Merski on 10.11.2019.
//

#pragma once


#include <llvm/IR/Module.h>

class BackendCompiler {

public:
    void run(llvm::Module *module, const std::string &outputFilename);
};

