//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include "NodeAST.h"
#include <string>
#include <vector>

class FunctionPrototypeNodeAST: public NodeAST {

private:
    std::string name;
    std::vector<std::string> arguments;

public:
    FunctionPrototypeNodeAST(std::string &name, std::vector<std::string> &arguments)
            : name(name), arguments(arguments) {
    }
};

