//
// Created by Piotr Merski on 11.11.2019.
//

#pragma once


#include <string>

struct SourceLocation {

    long startOffset;
    long endOffset;

    SourceLocation(long startOffset, long endOffset)
            : startOffset(startOffset), endOffset(endOffset) {
    }

    SourceLocation(long offset)
            : startOffset(offset), endOffset(offset) {
    }

    [[nodiscard]] inline long getLength() const {
        return endOffset - startOffset;
    }
};

