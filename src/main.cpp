#include <iostream>
#include <map>
#include <regex>
#include "Lexer.h"
#include "Parser.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    //TODO move functions to private scope in lexer/parser
    //TODO add functions
    //TODO display line of code with error and ^ indicating error
    if (argc > 1) {
        std::string fileName = std::string(argv[1]);
        Lexer lexer(fileName);
        lexer.printTokens();

        Parser parser(lexer.getTokenList());
        parser.printTree();
    }

    return 0;
}
