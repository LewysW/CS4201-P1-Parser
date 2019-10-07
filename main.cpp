#include <iostream>
#include <map>
#include <regex>
#include "Lexer.h"
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string fileName = std::string(argv[1]);
        Lexer lexer(fileName);
        lexer.printTokens();
    }

    return 0;
}
