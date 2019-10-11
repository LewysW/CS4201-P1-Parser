//#pragma once

#ifndef LEXER_H
#define LEXER_H
#include "Pattern.h"
#include "LexException.h"
#include "Token.h"
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>

class Lexer {
private:
    std::string fileContent;
    std::vector<Token> tokenList;
    inline static const std::vector<std::string> TOKEN_STRINGS {
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
            "PRINTLN", //println
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
public:
    explicit Lexer(std::string const& file);

    void printTokens();

    static void printTokens(const std::vector<Token>& tokens);

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
};

#endif


