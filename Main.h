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
            {TokenType::LPAREN, "\\("},
            {TokenType::RPAREN, "\\)"},
            {TokenType::PRINT, "print"},
            {TokenType::PRINTLN, "println"},
            {TokenType::COMMENT, "\\{-|-\\}"},
            {TokenType::VAR, "var"},
            {TokenType::GET, "get"},
            {TokenType::ASSIGNMENT, ":="},
            {TokenType::LOGICAL, "and|or|not"},
            //https://stackoverflow.com/questions/15937672/catch-the-relational-operators-with-regex
            {TokenType::RELOP, "<|<=|>=|>|=="},
            {TokenType ::ARITH, "\\+|-|\\/|\\*"},
            {TokenType::SEMI, ";"},
            {TokenType::PROGRAM, "program"},
            {TokenType::BEGIN, "begin"},
            {TokenType::END, "end"},
            {TokenType::INT, "[0-9]+"},
            {TokenType::REAL, "[+-]?([0-9]*)?[.][0-9]+"}
            //{TokenType::ID, "[a-zA-Z]([a-zA-Z]|[0-9])*"} //TODO expand ID values beyond letters and numbers
    };

    return patterns;
}
