//
// Created by Piotr Merski on 03.11.2019.
//

#include "ASTPrinterOutput.h"

void ASTPrinterOutput::print(const std::string &tag, const std::map<std::string, std::string> &attributes) {
    output << getIndent() << getTagString(tag);
    if (!attributes.empty())
        output << " " << getAttributesString(attributes);
    output << std::endl;
}

void ASTPrinterOutput::printChildNode(NodeASTVisitor *visitor,
                                      NodeAST &node, const std::string &tag,
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
    node.accept(visitor);
    indent -= childIndent.size();
}

std::string ASTPrinterOutput::getIndent() {
    if (skipNextIndent) {
        skipNextIndent = false;
        return "";
    }
    return std::string(indent, ' ');
}

std::string ASTPrinterOutput::getOutput() {
    return output.str();
}

std::string ASTPrinterOutput::getTagString(const std::string &tag) {
    return "[\x1B[34m" + tag + "\033[0m]";
}

std::string ASTPrinterOutput::getChildTagString(const std::string &tag) {
    return "{\x1B[32m" + tag + "\033[0m}";
}

std::string ASTPrinterOutput::getAttributesString(const std::map<std::string, std::string> &attributes) {
    std::stringstream result;
    for (auto it = attributes.begin(); it != attributes.end(); it++) {
        result << it->first << "=" << "\x1B[33m" << it->second << "\033[0m";
        if (std::next(it) != attributes.end())
            result << ", ";
    }
    return result.str();
}