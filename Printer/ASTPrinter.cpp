//
// Created by Piotr Merski on 20.10.2019.
//

#include "ASTPrinter.h"
#include "../NodeAST.h"

std::string ASTPrinter::print(NodeAST *node) {
    output = std::make_unique<ASTPrinterOutput>();
    node->accept(this);
    return output->getOutput();
}

void ASTPrinter::visitBinaryOperatorNode(BinaryOperatorNodeAST *node) {
    output->print("BinaryOperatorNodeAST", {
            {"operator", node->getOperatorText()},
    });

    output->printChildNode(this, *node->getLhs(), "lhs");
    output->printChildNode(this, *node->getRhs(), "rhs");
}

void ASTPrinter::visitCallNode(CallNodeAST *node) {
    output->print("CallNodeAST", {
            {"callee", node->getCallee()},
    });
    for (auto &argument : node->getArguments()) {
        output->printChildNode(this,*argument, "Argument");
    }
}

void ASTPrinter::visitFileNode(FileNodeAST *node) {
    output->print("FileNodeAST");
    for (auto &childNode : node->getNodes()) {
        output->printChildNode(this,*childNode);
    }
}

void ASTPrinter::visitFunctionBodyNode(FunctionBodyNodeAST *node) {
    output->print("FunctionBodyNodeAST");
    for (auto &childNode : node->getNodes()) {
        output->printChildNode(this,*childNode);
    }
}

void ASTPrinter::visitFunctionPrototypeNode(FunctionPrototypeNodeAST *node) {
    output->print("FunctionPrototypeNodeAST", {
            {"name", node->getName()}
    });
    for (auto &argument : node->getArguments()) {
        output->printChildNode(this,*argument, "Argument");
    }
}

void ASTPrinter::visitFunctionDefinitionNode(FunctionDefinitionNodeAST *node) {
    output->print("FunctionDefinitionNodeAST");
    output->printChildNode(this,*node->getPrototype(), "Prototype");
    output->printChildNode(this,*node->getBody(), "Body");
}

void ASTPrinter::visitNumberNode(NumberNodeAST *node) {
    output->print("NumberNodeAST", {
            {"value", std::to_string(node->getNumber())}
    });
}

void ASTPrinter::visitReferenceNode(ReferenceNodeAST *node) {
    output->print("ReferenceNodeAST", {
            {"name", node->getName()}
    });
}


