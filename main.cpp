#include <iostream>
#include <fstream>
#include "Tokenizer.h"
#include "ParsingException.h"
#include "Utilities/Console.h"
#include "NodeASTParser.h"
#include "IRGenerator.h"
#include "Printer/ASTPrinter.h"
#include "Utilities/Arguments.h"

void parse(const std::string &text, Arguments &arguments, Console *console);
void compileFile(const std::string &filename, Arguments &arguments);
void runConsole(Arguments &arguments);

int main(int argc, char *argv[]) {
    auto arguments = Arguments(argc, argv);

    auto inputFile = arguments.getOption("-i");
    if (inputFile.has_value())
        compileFile(*inputFile, arguments);
    else
        runConsole(arguments);

    return 0;
}

void compileFile(const std::string &filename, Arguments &arguments) {
    std::ifstream file(filename);
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string fileContent = fileStream.str();

    parse(fileContent, arguments, nullptr);
}

void runConsole(Arguments &arguments) {
    auto console = Console("kek-lang> ");
    console.begin([&](const std::string &inputText) {
        try {
            parse(inputText, arguments, &console);
        }
        catch (ParsingException &e) {
            console.printMarker(e.getOffset());
            Console::printMessage("Error: " + e.getMessage());
        }
    });
}

void parse(const std::string &text, Arguments &arguments, Console *console) {
    Tokenizer tokenizer(text);
    auto tokens = tokenizer.getTokens();
    if (arguments.isFlag("-dump-tokens")) {
        for (const auto &token : tokens) {
            if (console != nullptr)
                console->printMarker(token.offset, token.text.size());
            std::cout << "Token { " << token << " }" << std::endl;
        }
    }

    NodeASTParser parser(tokens);
    auto rootNode = parser.parse();

    if (arguments.isFlag("-dump-ast")) {
        ASTPrinter printer;
        std::cout << printer.print(rootNode.get()) << std::endl;
    }

    IRGenerator irGenerator;
    irGenerator.run(std::move(rootNode));
}