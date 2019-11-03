//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once

#include <string>
#include <memory>
#include "../Utilities/NodeASTVisitor.h"
#include "ASTPrinterOutput.h"

class NodeAST;

class ASTPrinter : private NodeASTVisitor {

private:
    std::unique_ptr<ASTPrinterOutput> output = nullptr;

public:
    std::string print(const NodeAST *node);

private:
    void visitBinaryOperatorNode(const BinaryOperatorNodeAST *node) override;
    void visitCallNode(const CallNodeAST *callNode) override;
    void visitFileNode(const FileNodeAST *fileNode) override;
    void visitFunctionBodyNode(const FunctionBodyNodeAST *functionBodyNode) override;
    void visitFunctionPrototypeNode(const FunctionPrototypeNodeAST *functionPrototypeNode) override;
    void visitFunctionDefinitionNode(const FunctionDefinitionNodeAST *functionDefinitionNode) override;
    void visitNumberNode(const NumberNodeAST *numberNode) override;
    void visitReferenceNode(const ReferenceNodeAST *referenceNode) override;
};

