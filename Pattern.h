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
        NEWLINE // \n
    };
}

