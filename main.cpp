#include <iostream>
#include "Tokenizer.h"
#include "ParsingException.h"
#include "Console.h"

int main() {

    auto console = Console("kek-lang> ");
    console.begin([&] (const std::string &inputText) {
        try {
            Tokenizer tokenizer(inputText);
            auto tokens = tokenizer.getTokens();
            for (const auto &token : tokens) {
                std::cout << "Token { " << token << " }" << std::endl;
            }
        }
        catch (ParsingException &e) {
            console.printMarker(e.getOffset());
            Console::printMessage("Error: " + e.getMessage());
        }
    });
    return 0;
}