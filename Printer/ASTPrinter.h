//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once

#include <string>
#include <memory>
#include "../NodeASTVisitor.h"
#include "ASTPrinterOutput.h"

class NodeAST;

class ASTPrinter : private NodeASTVisitor {

private:
    std::unique_ptr<ASTPrinterOutput> output = nullptr;

public:
    std::string print(NodeAST *node);

private:
    void visitBinaryOperatorNode(BinaryOperatorNodeAST *node) override;
    void visitCallNode(CallNodeAST *callNode) override;
    void visitFileNode(FileNodeAST *fileNode) override;
    void visitFunctionBodyNode(FunctionBodyNodeAST *functionBodyNode) override;
    void visitFunctionPrototypeNode(FunctionPrototypeNodeAST *functionPrototypeNode) override;
    void visitFunctionDefinitionNode(FunctionDefinitionNodeAST *functionDefinitionNode) override;
    void visitNumberNode(NumberNodeAST *numberNode) override;
    void visitReferenceNode(ReferenceNodeAST *referenceNode) override;
};

