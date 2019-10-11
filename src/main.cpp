#include <iostream>
#include <map>
#include <regex>
#include "Lexer.h"
#include "Parser.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string fileName = std::string(argv[1]);
        Lexer lexer(fileName);
        lexer.printTokens();

        Parser parser(lexer.getTokenList());
    }

    return 0;
}
