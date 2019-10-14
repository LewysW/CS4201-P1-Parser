#pragma once

#include "Pattern.h"
#include "ParseException.h"
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
public:
    explicit Lexer(std::string const& file);

    void printTokens();

    static void printTokens(const std::vector<Token>& tokens);

    std::string readFile(std::string const& file) const;

    std::vector<Token> tokenize() const;

    Pattern::TokenType isComment(std::string &s, unsigned long &tokLen, unsigned long &lineCount) const;

    Pattern::TokenType isStrLiteral(std::string &s, unsigned long &tokLen) const;

    Pattern::TokenType isOperator(std::string &stream, unsigned long &tokLen) const;

    Pattern::TokenType isKeyword(std::string &s, unsigned long &tokLen,
                                 std::map<std::string, Pattern::TokenType> const &keywords) const;

    Pattern::TokenType isNumeric(std::string &s, unsigned long &tokLen) const;

    Pattern::TokenType isIdentifier(std::string &s, unsigned long &tokLen) const;

    std::map<std::string, Pattern::TokenType> getKeywords() const;

    std::string buffer(std::string& stream) const;

    const std::string &getFileContent() const;

    const std::vector<Token> &getTokenList() const;

    inline static const std::vector<std::string> TOKEN_STRINGS {
            "NONE",
            "<", //Less than
            "<=", //Less than equal to
            ">", //Greater than
            ">=", //Greater than equal to
            "==", //Equal to
            ":=", //assignment
            ";", //Semi colon
            "+", // +
            "-", // -
            "/", // '/'
            "*", // *
            "STRING", //String literal
            "(", //Left paren
            ")", //Right paren
            "COMMENT", //Comment
            ",", // ,
            "begin", //begin
            "end", //end
            "program", //program
            "procedure", //procedure
            "return", //return
            "if", //if
            "then", // then
            "else", //else
            "while", //while
            "print", //print
            "println", //println
            "var", // var
            "get", // get
            "and", // and
            "or", // or
            "not", // not
            "true", // true
            "false", // false
            "NEWLINE", //\n
            "WHITESPACE", //\r \s \t
            "NUM", //sequence of digits
            "ID"
    };
};

