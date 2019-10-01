#pragma once
#include <string>

namespace Pattern {
    enum class TokenType {
        IF,
        THEN,
        ELSE,
        WHILE,
        LPAREN,
        RPAREN,
        PRINT,
        PRINTLN,
        COMMENT,
        VAR,
        GET,
        ASSIGNMENT,
        BOOL,
        LOGICAL,
        RELOP,
        ARITH,
        SEMI,
        PROGRAM,
        BEGIN,
        END,
        INT,
        REAL,
        ID
    };
}

