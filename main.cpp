#include <iostream>
#include "Tokenizer.h"

int main() {
    std::cout << "Welcome to Kek-lang" << std::endl;
    std::cout << "Type 'q' or 'quit' to stop program" << std::endl;
    std::cout << std::endl;

    std::string inputText;
    while (true) {
        std::cout << "kek-lang> ";
        std::getline(std::cin, inputText);

        if (inputText == "q" || inputText == "quit")
            break;

        Tokenizer tokenizer(inputText);
        auto tokens = tokenizer.getTokens();
        for (const auto &token : tokens) {
            std::cout << "Token { " << token << " }" << std::endl;
        }
    };

    std::cout << "Bye!" << std::endl;
    return 0;
}