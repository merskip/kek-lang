//
// Created by Piotr Merski on 20.10.2019.
//

#pragma once

#include <string>
#include <functional>
#include <sstream>
#include <map>

class NodeAST;

class NodeASTPrinter {

private:
    int indent = 0;
    bool skipNextIndent = false;
    std::stringstream output;

public:

    void print(const std::string &tag, const std::map<std::string, std::string> &attributes = {});

    void printChildNode(const NodeAST &node, const std::string &tag = "",
                        const std::map<std::string, std::string> &attributes = {});

    std::string getOutput();

private:
    std::string getIndent();

    static std::string getTagString(const std::string &tag);

    static std::string getChildTagString(const std::string &tag);

    static std::string getAttributesString(const std::map<std::string, std::string> &attributes);


};

