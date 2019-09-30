#include <iostream>
#include <map>
#include "Pattern.h"
using Pattern::TokenType;
using Pattern::patterns;

int main() {
    /**
     * Regular expressions check with:
     * https://regex101.com/
     */

    std::cout << "Hello, World!" << std::endl;

    std::map<TokenType, std::string>::iterator it;

    for (it = patterns.begin(); it != patterns.end(); it++) {
        printf("%d: ", it->first);
        std::cout << it->second << std::endl;
    }

    std::cout << TokenType::
    return 0;
}