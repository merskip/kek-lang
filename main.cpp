#include <iostream>
#include <fstream>
#include <algorithm>
#include "Lexer/Lexer.h"
#include "Utilities/ParsingException.h"
#include "Utilities/Console.h"
#include "ParserAST/NodeASTParser.h"
#include "Printer/ASTPrinter.h"
#include "Utilities/Arguments.h"
#include "Compiler/LLVMCompiler.h"
#include "BuiltinTypes.h"
#include "Compiler/BackendCompiler.h"

void parse(const std::string &text, Console *console, const std::optional<std::string> &filename);

void compileFile(const std::string &filename);

void runConsole();

std::string replaceExtension(const std::string &filename, const std::string &newExtension);

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

    std::string outputFilename = replaceExtension(filename, "o");
    try {
        parse(fileContent, nullptr, outputFilename);
    }
    catch (ParsingException &e) {
        auto location = e.getSourceLocation();

        std::cout << fileContent.substr(location.startOffset - 4, 4);
        std::cout << "[\x1B[31m" + fileContent.substr(location.startOffset, location.getLength()) + "\033[0m]";
        std::cout << fileContent.substr(location.endOffset, 4);
        std::cout << std::endl;
        std::cout << "Error: " << e.getMessage() << std::endl;
    }
}

void runConsole() {
    auto console = Console("kek-lang> ");
    console.begin([&](const std::string &inputText) {
        try {
            parse(inputText, &console, std::nullopt);
        }
        catch (ParsingException &e) {
            auto location = e.getSourceLocation();
            console.printMarker(location.startOffset, location.getLength());
            Console::printMessage("Error: " + e.getMessage());
        }
    });
}

void parse(const std::string &text, Console *console, const std::optional<std::string> &filename) {
    Lexer tokenizer(text, builtin::operators);
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

    LLVMCompiler llvmCompiler("kek-lang");
    llvmCompiler.compile(rootNode.get());

    auto module = llvmCompiler.getModule();
    if (arguments.isFlag("-dump-llvm-ir"))
        module->print(llvm::outs(), nullptr);

    BackendCompiler backendCompiler;
    backendCompiler.run(llvmCompiler.getModule(), filename.value_or("kek-console.o"));
}

std::string replaceExtension(const std::string &filename, const std::string &newExtension) {
    std::string::size_type indexOfDot = filename.find_last_of('.');
    std::string basename;
    if (indexOfDot != std::string::npos) {
        basename = filename.substr(0, indexOfDot);
    } else {
        basename = filename;
    }
    return basename + "." + newExtension;
}
