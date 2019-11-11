//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include "NodeAST.h"

struct BinaryOperatorNodeAST : public NodeAST {

    std::string operatorText;
    std::unique_ptr<NodeAST> lhs, rhs;

    BinaryOperatorNodeAST(const std::string &operatorText, std::unique_ptr<NodeAST> &lhs, std::unique_ptr<NodeAST> &rhs, SourceLocation location)
            : operatorText(operatorText), lhs(std::move(lhs)), rhs(std::move(rhs)), NodeAST(location) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitBinaryOperatorNode(this);
    }
};

