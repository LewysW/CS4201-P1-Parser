#pragma once
#include "Pattern.h"
#include <string>
#include <map>
#include <vector>
#include <regex>
#define TOKEN_NUM 17

class Lexer {
private:
    std::string fileContent;
    std::map<Pattern::TokenType, std::string> tokenTypes;
public:
    explicit Lexer(std::string const& file);

    std::string readFile(std::string const& file) const;

    std::vector<std::pair<Pattern::TokenType, std::string>> tokenize() const;

    Pattern::TokenType isOperator(std::string& stream, int& tokLen) const;

    const std::string &getFileContent() const;

    void setFileContent(const std::string &fileContent);

    //Allows for printing of token type strings
    const char* TOKEN_STRINGS[TOKEN_NUM] = {
            "NONE",
            "LT", //Less than
            "LTE", //Less than equal to
            "GT", //Greater than
            "GTE", //Greater than equal to
            "ASSIGN", //assignment
            "SEMI", //Semi colon
            "PLUS", // +
            "MINUS", // -
            "DIVIDE", // '/'
            "MULTIPLY", // *
            "QUOTE",
            "DQUOTE",
            "LPAREN",
            "RPAREN",
            "OPEN_COMMENT",
            "CLOSE_COMMENT"
    };
};


