#pragma once

#include <string>
#include <map>
#include "Pattern.h"

class Lexer {
private:
    std::string regex;

public:
    explicit Lexer(std::map<Pattern::TokenType, std::string> pairs);
    std::string getRegex() const;
    void setRegex(std::map<Pattern::TokenType, std::string> pairs);
};


