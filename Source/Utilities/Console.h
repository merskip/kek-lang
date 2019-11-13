//
// Created by Piotr Merski on 18.10.2019.
//

#pragma once

#include <string>
#include <functional>
#include <utility>

class Console {

private:
    std::string prompt;

public:
    explicit Console(std::string prompt)
            : prompt(std::move(prompt)) {
    }

    void begin(const std::function<void(const std::string &inputText)> &onInputText);

    void printMarker(long offset, long markerSize = 1);

    static void printMessage(const std::string &message);

private:
    static void printWelcome();

    void printPrompt();

    static std::string getInputText();

    static void printBye();

    static bool shouldQuit(const std::string &inputText);
};

