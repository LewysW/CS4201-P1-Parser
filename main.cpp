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

    std::map<TokenType, std::string>::iterator it;

    for (it = patterns.begin(); it != patterns.end(); it++) {
        printf("%d: ", it->first);
        std::cout << it->second << std::endl;
    }
    return 0;
}