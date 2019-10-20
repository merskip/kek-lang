//
// Created by Piotr Merski on 19.10.2019.
//

#pragma once

#include <ostream>
#include "../NodeASTPrinter.h"


class NodeAST {

public:
    virtual void print(NodeASTPrinter &printer) const = 0;
};
