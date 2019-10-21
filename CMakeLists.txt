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
        Tokenizer.cpp
        Console.cpp
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
        NodeASTPrinter.h
        NodeASTPrinter.cpp NodeAST/FunctionBodyNodeAST.h IRGenerator.cpp IRGenerator.h)

target_link_libraries(kek_lang LLVM)
