//
// Created by Piotr Merski on 03.11.2019.
//

#pragma once


#include <list>
#include <string>
#include <algorithm>
#include <optional>

class Arguments {

private:
    std::list<std::string> args;

public:
    void initialize(int argc, char *argv[]);

    bool isFlag(const std::string &flag);

    std::optional<std::string> getOption(const std::string &option);

};

static Arguments arguments;
