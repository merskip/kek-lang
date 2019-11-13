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

    virtual ReturnValue visitForValueBinaryOperatorNode(const BinaryOperatorNodeAST *node) = 0;
    virtual ReturnValue visitForValueCallNode(const CallNodeAST *node) = 0;
    virtual ReturnValue visitForValueFileNode(const FileNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionBodyNode(const FunctionBodyNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) = 0;
    virtual ReturnValue visitForValueFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) = 0;
    virtual ReturnValue visitForValueNumberNode(const NumberNodeAST *node) = 0;
    virtual ReturnValue visitForValueReferenceNode(const ReferenceNodeAST *node) = 0;

    void visitBinaryOperatorNode(const BinaryOperatorNodeAST *node) override {
        value = visitForValueBinaryOperatorNode(node);
    }

    void visitCallNode(const CallNodeAST *node) override {
        value = visitForValueCallNode(node);
    }

    void visitFileNode(const FileNodeAST *node) override {
        value = visitForValueFileNode(node);
    }

    void visitFunctionBodyNode(const FunctionBodyNodeAST *node) override {
        value = visitForValueFunctionBodyNode(node);
    }

    void visitFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) override {
        value = visitForValueFunctionPrototypeNode(node);
    }

    void visitFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) override {
        value = visitForValueFunctionDefinitionNode(node);
    }

    void visitNumberNode(const NumberNodeAST *node) override {
        value = visitForValueNumberNode(node);
    }

    void visitReferenceNode(const ReferenceNodeAST *node) override {
        value = visitForValueReferenceNode(node);
    };
};
