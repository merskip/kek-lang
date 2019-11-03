//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include "NodeAST.h"

class BinaryOperatorNodeAST : public NodeAST {

private:
    std::string operatorText;
    std::unique_ptr<NodeAST> lhs, rhs;

public:
    BinaryOperatorNodeAST(std::string &operatorText,
                          std::unique_ptr<NodeAST> &lhs,
                          std::unique_ptr<NodeAST> &rhs)
            : operatorText(operatorText),
              lhs(std::move(lhs)),
              rhs(std::move(rhs)) {
    }

    [[nodiscard]] const std::string &getOperatorText() const {
        return operatorText;
    }

    [[nodiscard]] const std::unique_ptr<NodeAST> &getLhs() const {
        return lhs;
    }

    [[nodiscard]] const std::unique_ptr<NodeAST> &getRhs() const {
        return rhs;
    }

    void accept(NodeASTVisitor *visitor) override {
        visitor->visitBinaryOperatorNode(this);
    }

    llvm::Value *generateCode(CompileContext *context) const override {
        auto lhsValue = lhs->generateCode(context);
        auto rhsValue = rhs->generateCode(context);

        if (operatorText == "+")
            return context->builder->CreateFAdd(lhsValue, rhsValue, "add");
        else if (operatorText == "-")
            return context->builder->CreateFSub(lhsValue, rhsValue, "sub");
        else if (operatorText == "/")
            return context->builder->CreateFDiv(lhsValue, rhsValue, "div");
        else if (operatorText == "*")
            return context->builder->CreateFMul(lhsValue, rhsValue, "mul");
        else
            throw "Unknown operator: " + operatorText;
    }

    void print(NodeASTPrinter &printer) const override {
        printer.print("BinaryOperatorNodeAST", {
                {"operator", operatorText},
        });

        printer.printChildNode(*lhs, "lhs");
        printer.printChildNode(*rhs, "rhs");
    }
};

