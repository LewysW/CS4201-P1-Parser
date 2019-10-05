#pragma once
#include <string>
#include <vector>

namespace Pattern {
    enum class TokenType {
        NONE,
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
        QUOTE, // '
        DQUOTE, // "
        LPAREN,
        RPAREN,
        OPEN_COMMENT,
        CLOSE_COMMENT
    };
}

