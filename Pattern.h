#pragma once
#include <string>

namespace Pattern {
    enum class TokenType {
        INT,
        REAL,
        ID,
        BOOL,
        IF,
        THEN,
        ELSE,
        WHILE,
        PRINT,
        PRINTLN,
        VAR,
        GET,
        ASSIGNMENT,
        LOGICAL,
        RELOP,
        SEMI,
        PROGRAM,
        BEGIN,
        END
    };

    std::map<TokenType, std::string> patterns {
            {TokenType::INT, "[0-9]+"},
            {TokenType::REAL, "[+-]?([0-9]*)?[.][0-9]+"},
            {TokenType::ID, "[a-zA-Z]([a-zA-Z]|[0-9])*"}, //TODO expand ID values beyond letters and numbers
            {TokenType::BOOL, "true|false"},
            {TokenType::IF, "\\bif"},
            {TokenType::THEN, "\\bthen\\b"},
            {TokenType::ELSE, "\\belse\\b"},
            {TokenType::WHILE, "\\bwhile"},
            {TokenType::PRINT, "\\bprint\\b"},
            {TokenType::PRINTLN, "\\bprintln\\b"},
            {TokenType::VAR, "\\bvar\\b"},
            {TokenType::GET, "\\bget\\b"},
            {TokenType::ASSIGNMENT, ":="},
            {TokenType::LOGICAL, "\\band\\b|\\bor\\b|\\bnot\\b"},
            //https://stackoverflow.com/questions/15937672/catch-the-relational-operators-with-regex
            {TokenType::RELOP, "(?:<=?|>=?|==|!=)"},
            {TokenType::SEMI, ";"},
            {TokenType::PROGRAM, "\\bprogram\\b"},
            {TokenType::BEGIN, "\\bbegin\\b"},
            {TokenType::END, "\\bend\\b"}
    };
}

