//
// Created by Piotr Merski on 20.10.2019.
//

#include <numeric>
#include "NodeASTPrinter.h"
#include "NodeAST/NodeAST.h"

void NodeASTPrinter::print(const std::string &tag, const std::map<std::string, std::string> &attributes) {
    output << getIndent() << getTagString(tag);
    if (!attributes.empty())
        output << " " << getAttributesString(attributes);
    output << std::endl;
}

void NodeASTPrinter::printChildNode(const NodeAST &node, const std::string &tag,
                                    const std::map<std::string, std::string> &attributes) {
    static const std::string childIndent = " - ";

    output << getIndent() << childIndent << getChildTagString(tag);
    if (!attributes.empty())
        output << " " << getAttributesString(attributes);
    output << std::endl;

    indent += childIndent.size();
    node.print(*this);
    indent -= childIndent.size();
}

std::string NodeASTPrinter::getIndent() {
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
