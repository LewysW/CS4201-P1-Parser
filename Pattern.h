#pragma once
#include <string>
#include <vector>

namespace Pattern {
    enum class TokenType {
        NONE = 0,
        LT, //Less than
        LTE, //Less than equal to
        GT, //Greater than
        GTE, //Greater than equal to
        ASSIGN, //assignment
        SEMI, //Semi colon
        PLUS, // +
        MINUS, // -
        DIVIDE, // '/'
        MULTIPLY, // *
        STRING, // String literals
        LPAREN, // (
        RPAREN, // )
        COMMENT, // coments {- -}
        COMMA,
        BEGIN,
        END,
        PROGRAM,
        PROCEDURE,
        RETURN,
        IF,
        THEN,
        ELSE,
        WHILE,
        PRINT,
        PRINTLN,
        VAR,
        GET,
        AND,
        OR,
        NOT,
        TRUE,
        FALSE,
        NEWLINE, // \n
        WHITESPACE,
        REAL,
        INT,
        ID
    };
}

