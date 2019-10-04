#pragma once
#include <string>
#include <vector>

namespace Pattern {
    enum class TokenType {
        LT, //Less than
        GT, //Greater than
        EQ, //Equal to (assignment)
        DEQ, //Double equal to
        LTE, //Less than equal to
        GTE, //Greater than equal to
        COL, //Colon
        SEMI, //Semi colon
        PLUS, // +
        MINUS, // -
        DIVIDE, // '/'
        MULTIPLY, // *
        INVALID
    };
}

