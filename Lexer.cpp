#include <iostream>
#include <fstream>
#include "Lexer.h"

using Pattern::TokenType;
using std::string;
using std::cout;
using std::endl;

Lexer::Lexer(string const& file) : fileContent(readFile(file))
{
}

/**
 * Reads file and converts to string
 * @param file - to read
 * @return string contents of file
 */
std::string Lexer::readFile(string const& file) const {
    std::ifstream inputFile;
    inputFile.open(file);

    if (!inputFile) {
        std::cout << "File " << file << " failed to open" << std::endl;
        exit(1);
    }

    /**
     * Reading file into string
     * https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c
     */
    std::string content(dynamic_cast<std::stringstream const&>(std::stringstream() << inputFile.rdbuf()).str());
    inputFile.close();
    return content;
}

/**
 * Generates a list of tokens from the file of the Lexer
 * @return list of tokens
 */
//TODO - handle errors with comments, string literals, and OTHER tokens
std::vector<std::pair<TokenType, string>> Lexer::tokenize() const {
    int lexemeStart = 0, lookahead = 0;
    //size_t len = getFileContent().length();
    //std::string content = getFileContent();
    std::string content = "<=>:;-/*+";
    size_t len = content.length();
    std::vector<std::pair<TokenType, string>> tokens;
    Pattern::TokenType token;
    cout << content << endl;
    while (lexemeStart < len) {
        std::string subStr = content.substr(lexemeStart, 1);

        //Checks for single character operators
        if (static_cast<int>(token = isOperator(subStr))) {
            tokens.emplace_back(std::make_pair(token, ""));
        }

        lexemeStart++;
    }

    for (std::pair<TokenType, string> p : tokens) {
        cout << TOKEN_STRINGS[static_cast<int>(p.first)] << " ";
    }

    return tokens;
}

Pattern::TokenType Lexer::isOperator(std::string& s) const {
    if (s == "<") {
        return TokenType::LT;
    } else if (s == ">") {
        return TokenType::GT;
    } else if (s == "=") {
        return TokenType::EQ;
    } else if (s == ":") {
        return TokenType::COL;
    } else if (s == ";") {
        return TokenType::SEMI;
    } else if (s == "+") {
        return TokenType::PLUS;
    } else if (s == "-") {
        return TokenType::MINUS;
    } else if (s == "/") {
        return TokenType::DIVIDE;
    } else if (s == "*") {
        return TokenType::MULTIPLY;
    } else {
        return TokenType::INVALID;
    }
}

/**
 * Creates a map defining the tokens to be lexed and their corresponding regex
 * @return map of tokens/regex
 *//*
std::map<TokenType, string> Lexer::createTokenMap() const {
    std::map<TokenType, std::string> patterns {
            {TokenType::BOOL, "true|false"},
            {TokenType::IF, "if"},
            {TokenType::THEN, "then"},
            {TokenType::ELSE, "else"},
            {TokenType::WHILE, "while"},
            {TokenType::PRINT, "print"},
            {TokenType::PRINTLN, "println"},
            {TokenType::VAR, "var"},
            {TokenType::GET, "get"},
            {TokenType::LOGICAL, "\\band\\b|\\bor\\b|\\bnot"},
            {TokenType::PROGRAM, "program"},
            {TokenType::PROCEDURE, "procedure"},
            {TokenType::RETURN, "return"},
            {TokenType::BEGIN, "begin"},
            {TokenType::END, "end"},
            {TokenType::ID, "[a-zA-Z]([a-zA-Z]|[0-9])*"},
            {TokenType::COMMENT, "\\{-|-\\}"},
            {TokenType::LPAREN, "\\("},
            {TokenType::RPAREN, "\\)"},
            {TokenType::DOUBLEQUOTE, "\""},
            {TokenType::SINGLEQUOTE, "\'"},
            {TokenType::ASSIGNMENT, ":="},
            //https://stackoverflow.com/questions/15937672/catch-the-relational-operators-with-regex
            {TokenType::RELOP, "<|<=|>=|>|=="},
            {TokenType ::ARITH, "\\+|-?=}|\\/|\\*"},
            {TokenType::SEMI, ";"},
            {TokenType::COMMA, ","},
            {TokenType::INT, "[0-9]+"},
            {TokenType::REAL, "[+-]?([0-9]*)?[.][0-9]+"},
            {TokenType::OTHER, "[!#$%&?@\\^\\_`\\|]"}

            //TODO - match string literals rather than quotes and IDs
    };

    return patterns;
}*/

const string &Lexer::getFileContent() const {
    return fileContent;
}

void Lexer::setFileContent(const string &fileContent) {
    Lexer::fileContent = fileContent;
}

