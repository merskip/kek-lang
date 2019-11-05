cmake_minimum_required(VERSION 3.10)
project(kek_lang)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(
        kek_lang
        main.cpp
        Lexer/Lexer.cpp
        NodeAST.h
        NodeAST/NodeAST.h
        NodeAST/NumberNodeAST.h
        NodeAST/NumberNodeAST.h
        NodeAST/ReferenceNodeAST.h
        NodeAST/BinaryOperatorNodeAST.h
        NodeAST/CallNodeAST.h
        NodeAST/FunctionPrototypeNodeAST.h
        NodeAST/FunctionDefinitionNodeAST.h
        NodeAST/FileNodeAST.h
        NodeASTParser.cpp
        NodeASTParser.h
        NodeAST/FunctionBodyNodeAST.h
        Utilities/NodeASTVisitor.h
        Utilities/NodeASTValueVisitor.h
        Printer/ASTPrinter.h
        Printer/ASTPrinter.cpp
        Printer/ASTPrinterOutput.cpp
        Printer/ASTPrinterOutput.h
        Utilities/Console.h
        Utilities/Console.cpp
        Utilities/Arguments.h
        Utilities/Arguments.cpp
        Compiler/LLVMCompiler.cpp
        Compiler/LLVMCompiler.h
        Compiler/VariablesScope.cpp
        Compiler/VariablesScope.h
        Lexer/OperatorDefinition.h
        BuiltinTypes.h)

target_link_libraries(kek_lang LLVM)
