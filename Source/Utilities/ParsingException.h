//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <exception>
#include <string>
#include <utility>

class ParsingException : public std::exception {

private:
    long offset;
    std::string message;

public:
    ParsingException(long offset, std::string message) : offset(offset), message(std::move(message)) {};

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }

    [[nodiscard]] long getOffset() const {
        return offset;
    }

    [[nodiscard]] std::string getMessage() const {
        return message;
    }
};