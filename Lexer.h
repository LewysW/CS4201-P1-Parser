#pragma once
#include "Pattern.h"
#include <string>
#include <map>
#include <vector>
#include <regex>
#define TOKEN_NUM 29
#define NULL_CHAR 0
#define BACKSPACE 9
#define HORIZONTAL_TAB 9
#define VERTICAL_TAB 11
#define CARRIAGE_RETURN 13
#define SPACE 32

class Lexer {
private:
    std::string fileContent;
public:
    explicit Lexer(std::string const& file);

    std::string readFile(std::string const& file) const;

    std::vector<std::pair<Pattern::TokenType, std::string>> tokenize() const;

    std::vector<std::pair<Pattern::TokenType, std::string>> match(bool matchID) const;

    std::map<Pattern::TokenType, std::string> createTokenMap() const;

    const std::string &getFileContent() const;

    void setFileContent(const std::string &fileContent);

    //Allows for printing of token type strings
    const char* TOKEN_STRINGS[TOKEN_NUM] = {
            "BOOL",
            "IF",
            "THEN",
            "ELSE",
            "WHILE",
            "PRINT",
            "PRINTLN",
            "VAR",
            "GET",
            "LOGICAL",
            "PROGRAM",
            "PROCEDURE",
            "RETURN",
            "BEGIN",
            "END",
            "ID",
            "COMMENT",
            "LPAREN",
            "RPAREN",
            "DOUBLEQUOTE",
            "SINGLEQUOTE",
            "ASSIGNMENT",
            "RELOP",
            "ARITH",
            "SEMI",
            "COMMA",
            "INT",
            "REAL",
            "OTHER"
    };
};


