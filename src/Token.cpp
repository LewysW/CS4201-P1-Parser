#include "Token.h"

Token::Token(Pattern::TokenType tok, std::string val, unsigned long line, unsigned long col) :
        type(tok),
        value(std::move(val)),
        lineNum(line),
        colNum(col)
{
}

Pattern::TokenType Token::getType() const {
    return type;
}

const std::string &Token::getValue() const {
    return value;
}

unsigned long Token::getLineNum() const {
    return lineNum;
}

unsigned long Token::getColNum() const {
    return colNum;
}
