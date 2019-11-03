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
    virtual void visitBinaryOperatorNode(BinaryOperatorNodeAST *node) = 0;
    virtual void visitCallNode(CallNodeAST *node) = 0;
    virtual void visitFileNode(FileNodeAST *node) = 0;
    virtual void visitFunctionBodyNode(FunctionBodyNodeAST *node) = 0;
    virtual void visitFunctionPrototypeNode(FunctionPrototypeNodeAST *node) = 0;
    virtual void visitFunctionDefinitionNode(FunctionDefinitionNodeAST *node) = 0;
    virtual void visitNumberNode(NumberNodeAST *node) = 0;
    virtual void visitReferenceNode(ReferenceNodeAST *node) = 0;
};
