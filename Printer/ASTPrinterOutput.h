//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once

#include <sstream>
#include "../NodeAST/NodeAST.h"

class ASTPrinterOutput {
private:
    int indent = 0;
    bool skipNextIndent = false;
    std::stringstream output;

public:

    void print(const std::string &tag, const std::map<std::string, std::string> &attributes = {});

    void printChildNode(NodeASTVisitor *visitor,
                        const NodeAST *node, const std::string &tag = "",
                        const std::map<std::string, std::string> &attributes = {});

    std::string getOutput();

private:

    std::string getIndent();

    static std::string getTagString(const std::string &tag);

    static std::string getChildTagString(const std::string &tag);

    static std::string getAttributesString(const std::map<std::string, std::string> &attributes);

};

