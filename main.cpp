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
    string test = "program fib;\n"
            "begin\n"
            "var n;\n"
            "var first := 0;\n"
            "var second :=1;\n"
            "var next;\n"
            "var c :=0 ;\n"
            "print \"enter the number of terms\";\n"
            "get n;\n"
            "while ( c < n)\n"
            "begin\n"
            "if ( c and 1)\n"
            "then begin next := c; end\n"
            "else begin\n"
            " next := first + second;\n"
            " second := next;\n"
            "end\n"
            "print next;\n"
            "c := c + 1;\n"
            "end\n"
            "end";

    std::map<TokenType, string> regPatterns = createMap();
    Lexer lexer(regPatterns);

    cout << lexer.getRegex() << endl;
    std::map<size_t, std::pair<string, string>> tokens;

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
