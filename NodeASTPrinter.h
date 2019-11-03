//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once

#include <string>
#include <functional>
#include <sstream>
#include <map>
#include "NodeASTVisitor.h"

class NodeAST;

class NodeASTPrinter : private NodeASTVisitor {

private:
    int indent = 0;
    bool skipNextIndent = false;
    std::stringstream output;

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

    void print(const std::string &tag, const std::map<std::string, std::string> &attributes = {});

    void printChildNode(NodeAST &node, const std::string &tag = "",
                        const std::map<std::string, std::string> &attributes = {});

    std::string getOutput();

    std::string getIndent();

    static std::string getTagString(const std::string &tag);

    static std::string getChildTagString(const std::string &tag);

    static std::string getAttributesString(const std::map<std::string, std::string> &attributes);


};

