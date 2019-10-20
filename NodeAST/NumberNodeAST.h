//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include "NodeAST.h"

class NumberNodeAST : public NodeAST {

private:
    double number;

public:
    explicit NumberNodeAST(double number) : number(number) {}

    [[nodiscard]] double getNumber() const {
        return number;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("NumberNodeAST", {
                {"value", std::to_string(number)}
        });
    }
};