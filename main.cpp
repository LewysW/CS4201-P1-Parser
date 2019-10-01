#include <iostream>
#include <map>
#include <regex>
#include "Lexer.h"
#include "Main.h"
using Pattern::TokenType;
using std::regex;
using std::string;
using std::sregex_iterator;
using std::cout;
using std::endl;

int main() {
    string test = "program Test\n"
            "begin\n"
            "{- define the procedure function -}\n"
            "procedure function( var x, var y )\n"
            "begin\n"
            "return x + y;\n"
            "end\n"
            "procedure main ()\n"
            "begin\n"
            "var result;\n"
            "{- call the procedure called\n"
            " function -}\n"
            "result := function(1, 2);\n"
            "print (result);\n"
            "end\n"
            "end";

    std::map<TokenType, string> regPatterns = createMap();
    Lexer lexer();

    //TODO change to use vector and have TokenType as first value in pair
    std::map<size_t, std::pair<string, string>> tokens;


    //TODO comment each section so I have an idea of what it does
    for (auto pat = regPatterns.begin(); pat != regPatterns.end(); ++pat) {
        regex r(pat->second, regex::extended);
        auto words_begin = sregex_iterator(test.begin(), test.end(), r);
        auto words_end = sregex_iterator();

        for (auto it = words_begin; it != words_end; ++it) {
            tokens[it->position()] = make_pair(it->str(), pat->second);
        }
    }

    for (auto token = tokens.begin(); token != tokens.end(); ++token) {
        cout << token->second.first << " " << token->second.second << endl;
    }
    return 0;
}
