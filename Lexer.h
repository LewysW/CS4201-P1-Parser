#pragma once
#include "Pattern.h"
#include <string>
#include <map>
#include <vector>
#include <regex>
#define TOKEN_NUM 13

class Lexer {
private:
    std::string fileContent;
    std::map<Pattern::TokenType, std::string> tokenTypes;
public:
    explicit Lexer(std::string const& file);

    std::string readFile(std::string const& file) const;

    std::vector<std::pair<Pattern::TokenType, std::string>> tokenize() const;

    Pattern::TokenType isOperator(std::string& chars) const;

    //std::map<Pattern::TokenType, std::string> createTokenMap() const;

    const std::string &getFileContent() const;

    void setFileContent(const std::string &fileContent);

    //Allows for printing of token type strings
    const char* TOKEN_STRINGS[TOKEN_NUM] = {
            "LT", //Less than
            "GT", //Greater than
            "EQ", //Equal to (assignment)
            "DEQ", //Double equal to
            "LTE", //Less than equal to
            "GTE", //Greater than equal to
            "COL", //Colon
            "SEMI", //Semi colon
            "PLUS", // +
            "MINUS", // -
            "DIVIDE", // '/'
            "MULTIPLY", // *
            "INVALID"
    };
};


