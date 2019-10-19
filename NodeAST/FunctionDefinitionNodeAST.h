//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once


#include <memory>
#include "NodeAST.h"
#include "FunctionPrototypeNodeAST.h"

class FunctionDefinitionNodeAST: public NodeAST {

private:
    std::unique_ptr<FunctionPrototypeNodeAST> prototype;
    std::unique_ptr<NodeAST> body;

public:
    FunctionDefinitionNodeAST(std::unique_ptr<FunctionPrototypeNodeAST> &prototype, std::unique_ptr<NodeAST> &body)
            : prototype(std::move(prototype)), body(std::move(body)) {
    }

    [[nodiscard]] const std::unique_ptr<FunctionPrototypeNodeAST> &getPrototype() const {
        return prototype;
    }

    [[nodiscard]] const std::unique_ptr<NodeAST> &getBody() const {
        return body;
    }
};

