#include <iostream>
#include <map>
#include <regex>
#include "Lexer.h"
using Pattern::TokenType;
using std::regex;
using std::string;
using std::sregex_iterator;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string fileName = std::string(argv[1]);
        Lexer lexer(fileName);
        /*std::vector<std::pair<TokenType, string>> tokens = lexer.tokenize();*/
        lexer.tokenize();
    }

    return 0;
}
