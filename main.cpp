#include <iostream>
#include <map>
#include "Lexer.h"
#include "Main.h"
using Pattern::TokenType;

int main() {
    Lexer lexer(createMap());

    std::cout << lexer.getRegex() << std::endl;

    /*std::map<TokenType, std::string>::iterator it;*/

    /*for (it = patterns.begin(); it != patterns.end(); it++) {
        printf("%d: ", it->first);
        std::cout << it->second << std::endl;
    }*/


    return 0;
}
