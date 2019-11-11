//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include "NodeAST.h"

struct ReferenceNodeAST: public NodeAST {

    std::string name;

    ReferenceNodeAST(std::string &name, SourceLocation location) : name(name), NodeAST(location) {}

    void accept(NodeASTVisitor *visitor) const override {
        visitor->visitReferenceNode(this);
    }
};

