#include <iostream>
#include <fstream>
#include "Lexer/Lexer.h"
#include "ParsingException.h"
#include "Utilities/Console.h"
#include "NodeASTParser.h"
#include "Printer/ASTPrinter.h"
#include "Utilities/Arguments.h"
#include "Compiler/LLVMCompiler.h"

void parse(const std::string &text, Console *console);
void compileFile(const std::string &filename);
void runConsole();

int main(int argc, char *argv[]) {
    arguments.initialize(argc, argv);

    auto inputFile = arguments.getOption("-i");
    if (inputFile.has_value())
        compileFile(*inputFile);
    else
        runConsole();

    return 0;
}

void compileFile(const std::string &filename) {
    std::ifstream file(filename);
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string fileContent = fileStream.str();

    parse(fileContent, nullptr);
}

void runConsole() {
    auto console = Console("kek-lang> ");
    console.begin([&](const std::string &inputText) {
        try {
            parse(inputText, &console);
        }
        catch (ParsingException &e) {
            console.printMarker(e.getOffset());
            Console::printMessage("Error: " + e.getMessage());
        }
    });
}

void parse(const std::string &text, Console *console) {
    Lexer tokenizer(text);
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

    LLVMCompiler compiler("kek-lang");
    compiler.compile(rootNode.get());
}