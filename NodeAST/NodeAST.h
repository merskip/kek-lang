//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <ostream>
#include "../Utilities/NodeASTVisitor.h"
#include "../Utilities/NodeASTValueVisitor.h"
#include "../Utilities/SourceLocation.h"

struct NodeAST {

    SourceLocation sourceLocation;

    NodeAST(const SourceLocation &sourceLocation)
            : sourceLocation(sourceLocation) {
    }

    virtual void accept(NodeASTVisitor *visitor) const = 0;

    template<typename ReturnValue>
    ReturnValue acceptForValue(NodeASTValueVisitor<ReturnValue> *valueVisitor) const {
        accept(valueVisitor);
        return valueVisitor->getValue();
    }
};
