//
// Created by Piotr Merski on 20.10.2019.
//

#include <numeric>
#include "NodeASTPrinter.h"
#include "NodeAST/NodeAST.h"
#include "NodeAST/BinaryOperatorNodeAST.h"
#include "NodeAST/CallNodeAST.h"
#include "NodeAST/FileNodeAST.h"
#include "NodeAST/FunctionBodyNodeAST.h"
#include "NodeAST/FunctionPrototypeNodeAST.h"
#include "NodeAST/FunctionDefinitionNodeAST.h"
#include "NodeAST/NumberNodeAST.h"
#include "NodeAST/ReferenceNodeAST.h"

std::string NodeASTPrinter::print(NodeAST *node) {
    indent = 0;
    skipNextIndent = false;
    output.clear();

    node->accept(this);
    return getOutput();
}

void NodeASTPrinter::visitBinaryOperatorNode(BinaryOperatorNodeAST *node) {
    print("BinaryOperatorNodeAST", {
            {"operator", node->getOperatorText()},
    });

    printChildNode(*node->getLhs(), "lhs");
    printChildNode(*node->getRhs(), "rhs");
}

void NodeASTPrinter::visitCallNode(CallNodeAST *node) {
    print("CallNodeAST", {
            {"callee", node->getCallee()},
    });
    for (auto &argument : node->getArguments()) {
        printChildNode(*argument, "Argument");
    }
}

void NodeASTPrinter::visitFileNode(FileNodeAST *node) {
    print("FileNodeAST");
    for (auto &childNode : node->getNodes()) {
        printChildNode(*childNode);
    }
}

void NodeASTPrinter::visitFunctionBodyNode(FunctionBodyNodeAST *node) {
    print("FunctionBodyNodeAST");
    for (auto &childNode : node->getNodes()) {
        printChildNode(*childNode);
    }
}

void NodeASTPrinter::visitFunctionPrototypeNode(FunctionPrototypeNodeAST *node) {
    print("FunctionPrototypeNodeAST", {
            {"name", node->getName()}
    });
    for (auto &argument : node->getArguments()) {
        printChildNode(*argument, "Argument");
    }
}

void NodeASTPrinter::visitFunctionDefinitionNode(FunctionDefinitionNodeAST *node) {
    print("FunctionDefinitionNodeAST");
    printChildNode(*node->getPrototype(), "Prototype");
    printChildNode(*node->getBody(), "Body");
}

void NodeASTPrinter::visitNumberNode(NumberNodeAST *node) {
    print("NumberNodeAST", {
            {"value", std::to_string(node->getNumber())}
    });
}

void NodeASTPrinter::visitReferenceNode(ReferenceNodeAST *node) {
    print("ReferenceNodeAST", {
            {"name", node->getName()}
    });
}

void NodeASTPrinter::print(const std::string &tag, const std::map<std::string, std::string> &attributes) {
    output << getIndent() << getTagString(tag);
    if (!attributes.empty())
        output << " " << getAttributesString(attributes);
    output << std::endl;
}

void NodeASTPrinter::printChildNode(NodeAST &node, const std::string &tag,
                                    const std::map<std::string, std::string> &attributes) {
    static const std::string childIndent = " - ";

    output << getIndent() << childIndent;
    if (!tag.empty())
        output << getChildTagString(tag);
    if (!attributes.empty())
        output << " " << getAttributesString(attributes);
    if (!tag.empty() || !attributes.empty())
        output << std::endl;
    else
        skipNextIndent = true;

    indent += childIndent.size();
    node.accept(this);
    indent -= childIndent.size();
}

std::string NodeASTPrinter::getIndent() {
    if (skipNextIndent) {
        skipNextIndent = false;
        return "";
    }
    return std::string(indent, ' ');
}

std::string NodeASTPrinter::getOutput() {
    return output.str();
}

std::string NodeASTPrinter::getTagString(const std::string &tag) {
    return "[" + tag + "]";
}

std::string NodeASTPrinter::getChildTagString(const std::string &tag) {
    return "{" + tag + "}";
}

std::string NodeASTPrinter::getAttributesString(const std::map<std::string, std::string> &attributes) {
    std::stringstream result;
    for (auto it = attributes.begin(); it != attributes.end(); it++) {
        result << it->first << "=" << it->second;
        if (std::next(it) != attributes.end())
            result << ", ";
    }
    return result.str();
}
