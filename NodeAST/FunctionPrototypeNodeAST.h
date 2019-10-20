//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include "NodeAST.h"
#include <string>
#include <vector>

class FunctionPrototypeNodeAST : public NodeAST {

private:
    std::string name;
    std::vector<std::unique_ptr<ReferenceNodeAST>> arguments;

public:
    FunctionPrototypeNodeAST(std::string &name, std::vector<std::unique_ptr<ReferenceNodeAST>> &arguments)
            : name(name), arguments(std::move(arguments)) {
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("FunctionPrototypeNodeAST", {
                {"name", name}
        });
        for (auto &argument : arguments) {
            printer.printChildNode(*argument, "Argument");
        }
    }
};

