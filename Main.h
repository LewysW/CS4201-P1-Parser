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
            {TokenType::IF, "\\bif"},
            {TokenType::THEN, "\\bthen\\b"},
            {TokenType::ELSE, "\\belse\\b"},
            {TokenType::WHILE, "\\bwhile"},
            {TokenType::LPAREN, "\\("},
            {TokenType::RPAREN, "\\)"},
            {TokenType::PRINT, "\\bprint\\b"},
            {TokenType::PRINTLN, "\\bprintln\\b"},
            {TokenType::COMMENT, "{-|-}"},
            {TokenType::VAR, "\\bvar\\b"},
            {TokenType::GET, "\\bget\\b"},
            {TokenType::ASSIGNMENT, ":="},
            {TokenType::LOGICAL, "\\band\\b|\\bor\\b|\\bnot\\b"},
            //https://stackoverflow.com/questions/15937672/catch-the-relational-operators-with-regex
            {TokenType::RELOP, "(?:<=?|>=?|==|!=)"},
            {TokenType ::ARITH, "\\+|-|\\/|\\*"},
            {TokenType::SEMI, ";"},
            {TokenType::PROGRAM, "\\bprogram\\b"},
            {TokenType::BEGIN, "\\bbegin\\b"},
            {TokenType::END, "\\bend\\b"},
            {TokenType::INT, "[0-9]+"},
            {TokenType::REAL, "[+-]?([0-9]*)?[.][0-9]+"},
            {TokenType::ID, "[a-zA-Z]([a-zA-Z]|[0-9])*"} //TODO expand ID values beyond letters and numbers
    };

    return patterns;
}
