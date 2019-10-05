#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "LexException.h"

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
std::vector<std::pair<TokenType, string>> Lexer::tokenize() const {
    unsigned long lexemeStart = 0;
    unsigned long newLines = 0;
    int tokLen = 1;
    std::string content = getFileContent();
    size_t len = content.length();
    std::vector<std::pair<TokenType, string>> tokens;
    Pattern::TokenType token;

    //TODO handle whitespace (increment newline count and reset character count on new line)
    //TODO handle comments and string literals - ADD STATE TO KNOW WHEN IN A LITERAL OR COMMENT
    //TODO handle keywords
    //TODO handle numbers
    //TODO handle Identifiers
    while (lexemeStart < len - 1) {
        try {
            std::string subStr = content.substr(lexemeStart, len);

            //Checks for single character operators
            if (static_cast<int>(token = isOperator(subStr, tokLen))) {
                tokens.emplace_back(std::make_pair(token, ""));
                cout << TOKEN_STRINGS[static_cast<int>(token)] << endl;
            }

            lexemeStart += tokLen;
        } catch (LexException& e) {
            cout << "Error: " << e.what() << ", line " << newLines + 1 << ", column " << lexemeStart;
            exit(1);
        }
    }

    for (std::pair<TokenType, string> p : tokens) {
        cout << TOKEN_STRINGS[static_cast<int>(p.first)] << " ";
    }

    return tokens;
}

Pattern::TokenType Lexer::isOperator(std::string& s, int& tokLen) const {
    std::string sub = s.substr(0, 2);
    char first = sub.at(0);
    char second = sub.at(1);
    tokLen = 1;

    switch (first) {
        case '<':
            if (second == '=') {
                tokLen++;
                return TokenType::LTE;
            } else {
                return TokenType::LT;
            }
        case '>':
            if (second == '=') {
                tokLen++;
                return TokenType::GTE;
            } else {
                return TokenType::GT;
            }
        case ':':
            if (second == '=') {
                tokLen++;
                return TokenType::ASSIGN;
            } else {
                throw LexException("Invalid token ':'");
            }
        case ';':
            return TokenType::SEMI;
        case '+':
            return TokenType::PLUS;
        case '-':
            if (second == '}') {
                tokLen++;
                return TokenType::CLOSE_COMMENT;
            } else {
                return TokenType::MINUS;
            }
        case '/':
            return TokenType::DIVIDE;
        case '*':
            return TokenType::MULTIPLY;
        case '\'':
            return TokenType::QUOTE;
        case '\"':
            return TokenType::DQUOTE;
        case '(':
            return TokenType::LPAREN;
        case ')':
            return TokenType::RPAREN;
        case '{':
            if (second == '-') {
                tokLen++;
                return TokenType::OPEN_COMMENT;
            } else {
                throw LexException("Invalid token: '{'");
            }
        default:
            return TokenType::NONE;
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

