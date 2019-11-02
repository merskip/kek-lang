//
// Created by Piotr Merski on 20.10.2019.
//

#include "IRGenerator.h"
#include <llvm/Support/raw_ostream.h>

void IRGenerator::run(std::unique_ptr<FileNodeAST> fileNode) {
    auto compileContext = std::make_unique<CompileContext>(&context, &module, &builder);
    fileNode->generateCode(compileContext.get());
    module.print(llvm::outs(), nullptr);
}
