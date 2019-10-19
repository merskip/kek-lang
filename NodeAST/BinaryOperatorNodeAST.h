//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include "NodeAST.h"

class BinaryOperatorNodeAST: public NodeAST {

private:
    char operatorCharacter;
    std::unique_ptr<NodeAST> lhs, rhs;

public:
    BinaryOperatorNodeAST(char operatorCharacter,
                          std::unique_ptr<NodeAST> lhs,
                          std::unique_ptr<NodeAST> rhs)
            : operatorCharacter(operatorCharacter),
              lhs(std::move(lhs)),
              rhs(std::move(rhs)) {
    }

    [[nodiscard]] char getOperatorCharacter() const {
        return operatorCharacter;
    }

    [[nodiscard]] const std::unique_ptr<NodeAST> &getLhs() const {
        return lhs;
    }

    [[nodiscard]] const std::unique_ptr<NodeAST> &getRhs() const {
        return rhs;
    }

};

