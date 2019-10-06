#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "LexException.h"

using Pattern::TokenType;
using std::string;
using std::cout;
using std::endl;

Lexer::Lexer(string const& file) :
        fileContent(readFile(file))
{
}

bool operator!(TokenType t) {
    return (t == TokenType::NONE);
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
    unsigned long lineCount = 1;
    unsigned long charCount = 1;
    int tokLen = 1;
    std::string content = getFileContent();
    size_t len = content.length();
    std::vector<std::pair<TokenType, string>> tokens;
    Pattern::TokenType token;

    while (lexemeStart < len - 1) {
        try {
            std::string subStr = content.substr(lexemeStart, len);

            //Parses comments
            if ((token = isComment(subStr, tokLen, lineCount)) != TokenType::NONE) {
                tokens.emplace_back(std::make_pair(token, subStr.substr(0, tokLen)));
            //Parses string literals
            } else if ((token = isStrLiteral(subStr, tokLen)) != TokenType::NONE) {
                tokens.emplace_back(std::make_pair(token, subStr.substr(0, tokLen)));
            //Parses operators
            } else if ((token = isOperator(subStr, tokLen)) != TokenType::NONE) {
                //If token is not a newline and not in a comment or string literal
                if (token != TokenType::NEWLINE && token != TokenType::WHITESPACE) {
                    tokens.emplace_back(std::make_pair(token, ""));
                } else if (token == TokenType::NEWLINE) {
                    lineCount++;
                    charCount = 0;
                }
            } else if ((token = isKeyword(subStr, tokLen)) != TokenType::NONE) {
                //TODO handle keywords
                //TODO handle numbers
                //TODO handle Identifiers
            }

            //Increments lexemeStart to the beginning of the current lexeme to parse
            lexemeStart += tokLen;

            //Increments the char count of the current line
            charCount += tokLen;
        } catch (LexException& e) {
            cout << "Error: " << e.what() << ", line " << lineCount << ", column " << charCount;
            exit(1);
        }
    }

    for (std::pair<TokenType, string> p : tokens) {
        cout << TOKEN_STRINGS[static_cast<int>(p.first)] << ": " << p.second << endl;
    }

    return tokens;
}

Pattern::TokenType Lexer::isComment(std::string& s, int& tokLen, unsigned long& lineCount) const {
    unsigned long len = s.length();
    tokLen = 0;

    if (len >= 2 && s.substr(0, 2) == "{-") {
        tokLen += 2;

        while (tokLen < len - 2) {
            if (s[tokLen + 1] == '\n') lineCount++;

            if (s.substr(static_cast<unsigned long>(tokLen), 2) == "-}") {
                tokLen += 2;
                return TokenType::COMMENT;
            }

            tokLen++;
        }

        throw LexException("Unclosed comment");
    } else {
        return TokenType::NONE;
    }
}

Pattern::TokenType Lexer::isStrLiteral(std::string& s, int& tokLen) const {
    unsigned long len = s.length();
    tokLen = 0;
    std::string symbol = s.substr(0 , 1);

    if (symbol == "\"" || symbol == "\'") {
        tokLen++;

        while (tokLen < len - 1) {
            if (s.substr(static_cast<unsigned long>(tokLen), 1) == symbol) {
                tokLen++;
                return TokenType::STRING;
            }

            tokLen++;
        }

        throw LexException("Unclosed string literal");
    } else {
        return TokenType::NONE;
    }
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
            return TokenType::MINUS;
        case '/':
            return TokenType::DIVIDE;
        case '*':
            return TokenType::MULTIPLY;
        case '(':
            return TokenType::LPAREN;
        case ')':
            return TokenType::RPAREN;
        case '\r':
        case '\n':
            return TokenType::NEWLINE;
        case '\t':
        case ' ':
            return TokenType::WHITESPACE;
        case ',':
            return TokenType::COMMA;
        default:
            return TokenType::NONE;
    }
}

Pattern::TokenType Lexer::isKeyword(std::string& stream, int& tokLen) const {
    unsigned long len = stream.length();
    unsigned long pos = 1;
    unsigned long lineCount = 0;
    std::string buffer;
    std::string lookahead;
    while (pos < len - 1) {
        pos++;
        buffer = stream.substr(0, pos);
        lookahead = buffer.substr(buffer.length() - 2, 2);

        if (isOperator(lookahead, tokLen) != TokenType::NONE
            || isComment(lookahead, tokLen, lineCount) != TokenType::NONE
            || isStrLiteral(lookahead, tokLen) != TokenType::NONE) {

            buffer = buffer.substr(0, buffer.length() - 2);
            break;
        }
    }

    cout << "--------------------Buffer-------------------:" << buffer << endl;

    return TokenType::NONE;
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

