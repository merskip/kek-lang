//
// Created by Piotr Merski on 20.10.2019.
//

#include "ASTPrinter.h"
#include "../NodeAST.h"

std::string ASTPrinter::print(const NodeAST *node) {
    output = std::make_unique<ASTPrinterOutput>();
    node->accept(this);
    return output->getOutput();
}

void ASTPrinter::visitBinaryOperatorNode(const BinaryOperatorNodeAST *node) {
    output->print("BinaryOperatorNodeAST", {
            {"operator", node->operatorText},
    });

    output->printChildNode(this, node->lhs.get(), "lhs");
    output->printChildNode(this, node->rhs.get(), "rhs");
}

void ASTPrinter::visitCallNode(const CallNodeAST *node) {
    output->print("CallNodeAST", {
            {"callee", node->callee},
    });
    for (auto &argument : node->arguments) {
        output->printChildNode(this, argument.get(), "Argument");
    }
}

void ASTPrinter::visitFileNode(const FileNodeAST *node) {
    output->print("FileNodeAST");
    for (auto &childNode : node->nodes) {
        output->printChildNode(this, childNode.get());
    }
}

void ASTPrinter::visitFunctionBodyNode(const FunctionBodyNodeAST *node) {
    output->print("FunctionBodyNodeAST");
    for (auto &childNode : node->nodes) {
        output->printChildNode(this, childNode.get());
    }
}

void ASTPrinter::visitFunctionPrototypeNode(const FunctionPrototypeNodeAST *node) {
    output->print("FunctionPrototypeNodeAST", {
            {"name", node->name}
    });
    for (auto &argument : node->arguments) {
        output->printChildNode(this, argument.get(), "Argument");
    }
}

void ASTPrinter::visitFunctionDefinitionNode(const FunctionDefinitionNodeAST *node) {
    output->print("FunctionDefinitionNodeAST");
    output->printChildNode(this, node->prototype.get(), "Prototype");
    output->printChildNode(this, node->body.get(), "Body");
}

void ASTPrinter::visitNumberNode(const NumberNodeAST *node) {
    output->print("NumberNodeAST", {
            {"value", std::to_string(node->number)}
    });
}

void ASTPrinter::visitReferenceNode(const ReferenceNodeAST *node) {
    output->print("ReferenceNodeAST", {
            {"name", node->name}
    });
}
