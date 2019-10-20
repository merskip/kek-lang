//
// Created by Piotr Merski on 18.10.2019.
//

#include <iostream>
#include "Console.h"

void Console::begin(const std::function<void(const std::string &inputText)> &onInputText) {
    printWelcome();

    while (true) {
        printPrompt();
        auto inputText = getInputText();
        if (shouldQuit(inputText)) {
            printBye();
            break;
        }
        onInputText(inputText);
    }
}

void Console::printMarker(long offset, long markerSize) {
    auto offsetWithPrompt = offset + prompt.size();
    auto padding = std::string(offsetWithPrompt, ' ');
    std::cout << padding << std::string(markerSize, '^') << ' ';
}

void Console::printMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void Console::printWelcome() {
    std::cout << "Welcome to Kek-lang" << std::endl;
    std::cout << "Type 'q' or 'quit' to stop program" << std::endl;
    std::cout << std::endl;
}

void Console::printPrompt() {
    std::cout << prompt;
}

void Console::printBye() {
    std::cout << "Bye!" << std::endl;
}

std::string Console::getInputText() {
    std::string inputText;
    std::getline(std::cin, inputText);
    return inputText;
}

bool Console::shouldQuit(const std::string& inputText) {
    return inputText == "q" || inputText == "quit";
}

