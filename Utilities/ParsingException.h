//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <exception>
#include <string>
#include <utility>
#include "SourceLocation.h"

class ParsingException : public std::exception {

private:
    SourceLocation sourceLocation;
    std::string message;

public:
    ParsingException(long sourceOffset, std::string message)
            : sourceLocation(SourceLocation(sourceOffset, sourceOffset)), message(std::move(message)) {
    };

    ParsingException(SourceLocation sourceLocation, std::string message)
            : sourceLocation(sourceLocation), message(std::move(message)) {
    };

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

    const SourceLocation &getSourceLocation() const {
        return sourceLocation;
    }

    [[nodiscard]] std::string getMessage() const {
        return message;
    }
};