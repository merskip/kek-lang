//
// Created by Piotr Merski on 03.11.2019.
//

#include "Arguments.h"

void Arguments::initialize(int argc, char **argv) {
    args.clear();
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
}

bool Arguments::isFlag(const std::string &flag) {
    return std::find(args.begin(), args.end(), flag) != args.end();
}

std::optional<std::string> Arguments::getOption(const std::string &option) {
    auto optionIter = std::find(args.begin(), args.end(), option);
    if (optionIter == args.end())
        return std::nullopt;
    auto valueIter = std::next(optionIter);
    if (optionIter == args.end())
        return std::nullopt;
    return *valueIter;
}
