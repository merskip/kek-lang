//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once


class BinaryOperatorNodeAST;

class CallNodeAST;

class FileNodeAST;

class FunctionBodyNodeAST;

class FunctionPrototypeNodeAST;

class FunctionDefinitionNodeAST;

class NumberNodeAST;

class ReferenceNodeAST;

class NodeASTVisitor {

public:
    virtual void visitBinaryOperatorNode(BinaryOperatorNodeAST *binaryOperatorNode) = 0;

    virtual void visitCallNode(CallNodeAST *callNode) = 0;

    virtual void visitFileNode(FileNodeAST *fileNode) = 0;

    virtual void visitFunctionBodyNode(FunctionBodyNodeAST *functionBodyNode) = 0;

    virtual void visitFunctionPrototypeNode(FunctionPrototypeNodeAST *functionPrototypeNode) = 0;

    virtual void visitFunctionDefinitionNode(FunctionDefinitionNodeAST *functionDefinitionNode) = 0;

    virtual void visitNumberNode(NumberNodeAST *numberNode) = 0;

    virtual void visitReferenceNode(ReferenceNodeAST *referenceNode) = 0;
};
