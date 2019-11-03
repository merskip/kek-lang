//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once


#include "NodeASTVisitor.h"

template<typename ReturnValue>
class NodeASTValueVisitor: public NodeASTVisitor {

private:
    ReturnValue value;

public:

    [[nodiscard]] ReturnValue getValue() {
        return value;
    }

    virtual ReturnValue visitForValueBinaryOperatorNode(BinaryOperatorNodeAST *node) = 0;
    virtual ReturnValue visitForValueCallNode(CallNodeAST *node) = 0;
    virtual ReturnValue visitForValueFileNode(FileNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionBodyNode(FunctionBodyNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionPrototypeNode(FunctionPrototypeNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionDefinitionNode(FunctionDefinitionNodeAST *node) = 0;
    virtual ReturnValue visitForValueNumberNode(NumberNodeAST *node) = 0;
    virtual ReturnValue visitForValueReferenceNode(ReferenceNodeAST *node) = 0;

    void visitBinaryOperatorNode(BinaryOperatorNodeAST *node) override {
        value = visitForValueBinaryOperatorNode(node);
    }

    void visitCallNode(CallNodeAST *node) override {
        value = visitForValueCallNode(node);
    }

    void visitFileNode(FileNodeAST *node) override {
        value = visitForValueFileNode(node);
    }

    void visitFunctionBodyNode(FunctionBodyNodeAST *node) override {
        value = visitForValueFunctionBodyNode(node);
    }

    void visitFunctionPrototypeNode(FunctionPrototypeNodeAST *node) override {
        value = visitForValueFunctionPrototypeNode(node);
    }

    void visitFunctionDefinitionNode(FunctionDefinitionNodeAST *node) override {
        value = visitForValueFunctionDefinitionNode(node);
    }

    void visitNumberNode(NumberNodeAST *node) override {
        value = visitForValueNumberNode(node);
    }

    void visitReferenceNode(ReferenceNodeAST *node) override {
        value = visitForValueReferenceNode(node);
    };
};
