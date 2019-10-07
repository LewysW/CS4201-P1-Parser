#pragma once
#include "Pattern.h"
#include "Token.h"
#include <string>
#include <map>
#include <vector>
#include <regex>
#define TOKEN_NUM 39

class Lexer {
private:
    std::string fileContent;
    std::vector<Token> tokenList;
public:
    explicit Lexer(std::string const& file);

    void printTokens();

    std::string readFile(std::string const& file) const;

    std::vector<Token> tokenize() const;

    Pattern::TokenType isComment(std::string& s, int& tokLen, unsigned long& lineCount) const;

    Pattern::TokenType isStrLiteral(std::string& s, int& tokLen) const;

    Pattern::TokenType isOperator(std::string& stream, int& tokLen) const;

    Pattern::TokenType isKeyword(std::string& s, int& tokLen, std::map<std::string, Pattern::TokenType> const& keywords) const;

    Pattern::TokenType isNumeric(std::string& s, int& tokLen) const;

    Pattern::TokenType isIdentifier(std::string& s, int& tokLen) const;

    std::map<std::string, Pattern::TokenType> getKeywords() const;

    std::string buffer(std::string& stream) const;

    const std::string &getFileContent() const;

    const std::vector<Token> &getTokenList() const;

    //Allows for printing of token type strings
    const char* TOKEN_STRINGS[TOKEN_NUM] = {
            "NONE",
            "LT", //Less than
            "LTE", //Less than equal to
            "GT", //Greater than
            "GTE", //Greater than equal to
            "EQ", //Equal to
            "ASSIGN", //assignment
            "SEMI", //Semi colon
            "PLUS", // +
            "MINUS", // -
            "DIVIDE", // '/'
            "MULTIPLY", // *
            "STRING", //String literal
            "LPAREN", //Left paren
            "RPAREN", //Right paren
            "COMMENT", //Comment
            "COMMA", // ,
            "BEGIN", //begin
            "END", //end
            "PROGRAM", //program
            "PROCEDURE", //procedure
            "RETURN", //return
            "IF", //if
            "THEN", // then
            "ELSE", //else
            "WHILE", //while
            "PRINT", //print
            "PRINTLN", //print
            "VAR", // var
            "GET", // get
            "AND", // and
            "OR", // or
            "NOT", // not
            "TRUE", // true
            "FALSE", // false
            "NEWLINE", //\n
            "WHITESPACE", //\r \s \t
            "NUM", //sequence of digits
            "ID"
    };
};


