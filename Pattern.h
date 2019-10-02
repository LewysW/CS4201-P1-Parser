#pragma once
#include <string>
#include <vector>

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
        COMMA,
        INT,
        REAL
    };
}

