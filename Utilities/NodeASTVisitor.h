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
    virtual void visitBinaryOperatorNode(const BinaryOperatorNodeAST *node) = 0;
    virtual void visitCallNode(const CallNodeAST *node) = 0;
    virtual void visitFileNode(const FileNodeAST *node) = 0;
    virtual void visitFunctionBodyNode(const FunctionBodyNodeAST *node) = 0;
    virtual void visitFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) = 0;
    virtual void visitFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) = 0;
    virtual void visitNumberNode(const NumberNodeAST *node) = 0;
    virtual void visitReferenceNode(const ReferenceNodeAST *node) = 0;
};
