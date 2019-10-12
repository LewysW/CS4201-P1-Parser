#pragma once

#include <string>
#include "Pattern.h"

class Token {
private:
    Pattern::TokenType type;
    std::string value;
    unsigned long lineNum;
    unsigned long colNum;

public:
    Token(Pattern::TokenType tok, std::string val, unsigned long line, unsigned long col);

    Pattern::TokenType getType() const;

    const std::string &getValue() const;

    unsigned long getLineNum() const;

    unsigned long getColNum() const;
};


