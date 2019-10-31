#include <iostream>
#include <memory>
#include "Tokenizer.h"
#include "ParsingException.h"
#include "Console.h"
#include "NodeASTParser.h"
#include "IRGenerator.h"

int main() {

    auto console = Console("kek-lang> ");
    console.begin([&] (const std::string &inputText) {
        try {
            Tokenizer tokenizer(inputText);
            auto tokens = tokenizer.getTokens();
            for (const auto &token : tokens) {
                console.printMarker(token.offset, token.text.size());
                std::cout << "Token { " << token << " }" << std::endl;
            }

            NodeASTParser parser(tokens);
            auto rootNode = parser.parse();

            NodeASTPrinter printer;
            rootNode->print(printer);
            std::cout << printer.getOutput() << std::endl;

            IRGenerator irGenerator;
            irGenerator.run(std::move(rootNode));
        }
        catch (ParsingException &e) {
            console.printMarker(e.getOffset());
            Console::printMessage("Error: " + e.getMessage());
        }
    });
    return 0;
}