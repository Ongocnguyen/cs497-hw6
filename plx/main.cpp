#include <cassert>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/lexer/Lexer.hpp>
#include <plx/literal/InputStream.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/HashCode.hpp>
#include <plx/object/Object.hpp>

PLX::HashTable* parseOptions(int argc, char** argv) {
    PLX::HashTable* argMap = new PLX::HashTable();
    PLX::HashTable* bindings = new PLX::HashTable();
    PLX::Queue* switches = new PLX::Queue();
    PLX::Queue* positional = new PLX::Queue();
    PLX::Queue* extra = new PLX::Queue();
    argMap->put(PLX::Symbol::create("ProgName"), new PLX::String(argv[0]));
    int state = 0;
    PLX::String* key = nullptr;
    for (int n=1; n<argc; n++) {
        PLX::String* argString = new PLX::String(argv[n]);
        switch (state) {
            case 0:
                if (argString->startsWith("-") || argString->startsWith("--")) {
                    int argLen;
                    assert(argString->length(argLen));
                    if (argLen == 2) {
                        state = 2;
                    }
                    else {
                        key = argString->stripLeft('-');
                        state = 1;
                    }
                }
                else {
                    positional->enq(argString);
                }
                break;
            case 1:
                if (argString->startsWith("-") || argString->startsWith("--")) {
                    switches->enq(key);
                    key = argString->stripLeft('-');
                }
                else {
                    bindings->put(key, argString);
                    key = nullptr;
                    state = 0;
                }
                break;
            case 2:
                extra->enq(argString);
                break;
            default:
                assert(false);
        }
    }
    if (key != nullptr) {
        switches->enq(key);
        key = nullptr;
    }
    argMap->put(PLX::Symbol::create("Bindings"), bindings);
    argMap->put(PLX::Symbol::create("Extra"), extra->asList());
    argMap->put(PLX::Symbol::create("Positional"), positional->asList());
    argMap->put(PLX::Symbol::create("Switches"), switches->asList());
    return argMap;
}

void setup() {
    PLX::GLOBALS = new PLX::Globals();
    PLX::GLOBALS->initializeAll();
}

void shutdown() {
    delete PLX::GLOBALS;
}

void readEvalPrint() {
    PLX::Lexer lexer; // Create a new Lexer instance in the PLX namespace
    std::cout << "PLX> "; // Display the prompt "PLX> "
    std::string input;
    std::getline(std::cin, input); // Read a string from the user
    
    if (input == "exit") {
        return; // Terminate the function if the user enters "exit"
    }
    
    PLX::InputStream inputStream(input); // Create an InputStream instance from the input string
    
    PLX::List* tokens = nullptr;
    PLX::Object* errorValue = nullptr;
    
    bool success = lexer.tokenize(&inputStream, tokens, errorValue); // Call the tokenize function
    // Print the input string
    std::cout << "Input string = '" << input << "'\n";
    
    if (success) {
        // Tokens are valid, display them
        std::cout << "Lexer tokens = ";
        if (tokens != nullptr) {
            std::cout << tokens->toString() << std::endl;
            
            // Parse the tokens using the parser
            PLX::Object* parsedExpr;
            if (PLX::pRequireAny(tokens, parsedExpr)) {
                // Evaluate the parsed expression
                PLX::Evaluator evaluator;
                PLX::Object* result = evaluator.evalExpr(parsedExpr);
                
                // Display the evaluation result
                std::cout << "Evaluation result: " << result->toString() << std::endl;
            } else {
                std::cout << "Parsing failed" << std::endl;
            }
        } else {
            std::cout << "Empty" << std::endl;
        }
    } else {
        // Tokens are invalid, display the error
        std::cout << "Error: " << errorValue->toString() << std::endl;
    }
    
    readEvalPrint(); // Call readEvalPrint recursively for continuous prompting
}

void repLoop() {
    readEvalPrint(); // Call the readEvalPrint function in an unbounded loop
}

int main(int argc, char** argv) {
    setup();
    PLX::HashTable* argMap = parseOptions(argc, argv);
    PLX::GLOBALS->SetArgMap(argMap);
    // std::cout << "ArgMap = " << argMap << "\n";
    readEvalPrint();
    shutdown();
    repLoop();
    return 0;
}

