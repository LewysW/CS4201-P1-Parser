#pragma once
#include <string>

namespace Pattern {
    enum class TokenType {
        BOOL,
        IF,
        THEN,
        ELSE,
        WHILE,
        PRINT,
        PRINTLN,
        VAR,
        GET,
        LOGICAL,
        PROGRAM,
        PROCEDURE,
        RETURN,
        BEGIN,
        END,
        ID,
        COMMENT,
        LPAREN,
        RPAREN,
        ASSIGNMENT,
        RELOP,
        ARITH,
        SEMI,
        INT,
        REAL
    };
}

