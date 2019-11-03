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
};

