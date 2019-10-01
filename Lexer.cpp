#include "Lexer.h"
using Pattern::TokenType;

Lexer::Lexer(std::map<Pattern::TokenType, std::string> pairs) {
    setRegex(std::move(pairs));
}

std::string Lexer::getRegex() const {
    return regex;
}

//https://stackoverflow.com/questions/34229328/writing-a-very-simple-lexical-analyser-in-c
void Lexer::setRegex(std::map<Pattern::TokenType, std::string> pairs) {
    for (auto const& p : pairs) {
        regex += "(" + p.second + ")|";
    }
    regex = regex.substr(0, regex.size() - 1);
}