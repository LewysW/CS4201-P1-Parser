#pragma once

#include <map>
#include "Pattern.h"
using Pattern::TokenType;

/**
     * Regular expressions checked with:
     * https://regex101.com/
     */
std::map<Pattern::TokenType, std::string> createMap() {
    std::map<TokenType, std::string> patterns {
            {TokenType::BOOL, "true|false"},
            {TokenType::IF, "if"},
            {TokenType::THEN, "then"},
            {TokenType::ELSE, "else"},
            {TokenType::WHILE, "while"},
            {TokenType::PRINT, "print"},
            {TokenType::PRINTLN, "println"},
            {TokenType::VAR, "var"},
            {TokenType::GET, "get"},
            {TokenType::LOGICAL, "and|or|not"},
            {TokenType::PROGRAM, "program"},
            {TokenType::PROCEDURE, "procedure"},
            {TokenType::RETURN, "return"},
            {TokenType::BEGIN, "begin"},
            {TokenType::END, "end"},
            {TokenType::ID, "foo"}, //TODO expand ID values beyond letters and numbers
            {TokenType::COMMENT, "\\{-|-\\}"},
            {TokenType::LPAREN, "\\("},
            {TokenType::RPAREN, "\\)"},
            {TokenType::ASSIGNMENT, ":="},
            //https://stackoverflow.com/questions/15937672/catch-the-relational-operators-with-regex
            {TokenType::RELOP, "<|<=|>=|>|=="},
            {TokenType ::ARITH, "\\+|-?=}|\\/|\\*"},
            {TokenType::SEMI, ";"},
            {TokenType::INT, "[0-9]+"},
            {TokenType::REAL, "[+-]?([0-9]*)?[.][0-9]+"}
    };

    /*std::string strRegex;

    for (auto const& p : patterns) {
        if (p.first == TokenType::ID) break;

        strRegex += p.second + "|";
    }

    strRegex = strRegex.substr(0, strRegex.size() - 1);
    strRegex = "(?!" + strRegex;
    strRegex += "\\b)\\b\\w+";

    patterns[TokenType::ID] = strRegex;
    std::cout << strRegex << std::endl;*/
    return patterns;
}
