//
// Created by Piotr Merski on 10.11.2019.
//

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Target/TargetMachine.h>
#include "BackendCompiler.h"

void BackendCompiler::run(llvm::Module *module, const std::string &outputFilename) {
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    module->setTargetTriple(targetTriple);

    std::string err;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, err);

    llvm::TargetOptions opt;
    llvm::TargetMachine *targetMachine = target->createTargetMachine(module->getTargetTriple(), "generic", "", opt, llvm::None);
    module->setDataLayout(targetMachine->createDataLayout());

    std::error_code errFile;
    std::unique_ptr<llvm::ToolOutputFile> outputFile = std::make_unique<llvm::ToolOutputFile>(outputFilename, errFile, llvm::sys::fs::F_Text);
    llvm::raw_pwrite_stream &outputStream = outputFile->os();

    llvm::legacy::PassManager pass;
    targetMachine->addPassesToEmitFile(pass, outputStream, llvm::TargetMachine::CGFT_ObjectFile, true, nullptr);
    pass.run(*module);
    outputStream.flush();
    outputFile->keep();
}

