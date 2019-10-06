#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "LexException.h"

using Pattern::TokenType;
using std::string;
using std::cout;
using std::endl;
using std::map;

Lexer::Lexer(string const& file) :
        fileContent(readFile(file)),
        tokenList(tokenize())
{
}

void Lexer::printTokens() {
    std::string tokStr;

    for (std::pair<TokenType, string> p : getTokenList()) {
        tokStr = TOKEN_STRINGS[static_cast<int>(p.first)];
        tokStr += (p.second.empty()) ? "" : (": " + p.second);
        cout << tokStr << endl;
    }
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
    //Stores a list of keywords
    map<string, TokenType> keywords = getKeywords();

    //Tracks the start of the lexeme to be parsed
    unsigned long lexemeStart = 0;

    //Tracks the current line/char counts
    unsigned long lineCount = 1;
    unsigned long charCount = 1;

    //Stores the length of the current token
    int tokLen = 1;

    //Gets the file content and length of the file
    std::string content = getFileContent();
    size_t len = content.length();

    //Stores the list of parsed tokens and the current token
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
            } else {
                std::string lexeme = buffer(subStr);

                //Parses keywords
                if ((token = isKeyword(lexeme, tokLen, keywords)) != TokenType::NONE) {
                    tokens.emplace_back(std::make_pair(token, ""));
                //Parses ints or real numbers
                } else if ((token = isNumeric(lexeme, tokLen)) != TokenType::NONE) {
                    tokens.emplace_back(std::make_pair(token, lexeme));
                } else if ((token = isIdentifier(lexeme, tokLen)) != TokenType::NONE) {
                    tokens.emplace_back(std::make_pair(token, lexeme));
                } else {
                    throw LexException("Invalid token");
                }
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
    return tokens;
}

/**
 * Returns a string buffer containing a delimited lexeme to be lexed
 * @param stream - token stream
 * @param tokLen - lenght of
 * @return
 */
std::string Lexer::buffer(std::string& stream) const {
    unsigned long len = stream.length();
    unsigned long pos = 1;
    unsigned long lineCount = 0;
    int tokLen = 0;
    std::string buffer;
    std::string lookahead;


    while (pos < len) {
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

    return buffer;
}

Pattern::TokenType Lexer::isComment(std::string& s, int& tokLen, unsigned long& lineCount) const {
    unsigned long len = s.length();
    tokLen = 0;
    unsigned long lines = 0;

    if (len >= 2 && s.substr(0, 2) == "{-") {
        tokLen += 2;

        while (tokLen < len) {
            if (s[tokLen + 1] == '\n') lines++;

            if (s.substr(static_cast<unsigned long>(tokLen), 2) == "-}") {
                tokLen += 2;
                lineCount += lines;
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
        case '=':
            if (second == '=') {
                tokLen++;
                return TokenType::EQ;
            } else {
                throw LexException("Invalid token '='");
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
        case '\n':
                return TokenType::NEWLINE;
        case '\t':
        case ' ':
        case '\r':
            return TokenType::WHITESPACE;
        case ',':
            return TokenType::COMMA;
        default:
            return TokenType::NONE;
    }
}

Pattern::TokenType Lexer::isKeyword(string& s, int& tokLen, map<string, TokenType> const& keywords) const {
    tokLen = static_cast<int>(s.length());

    if (keywords.find(s) != keywords.end()) {
        return keywords.at(s);
    } else {
        return TokenType::NONE;
    }
}

Pattern::TokenType Lexer::isNumeric(string& s, int& tokLen) const {
    tokLen = static_cast<int>(s.length());

    //Checks for valid number
    for (char c : s) {
        if (c < '0' || c > '9') {
            return TokenType::NONE;
        }
    }

    return TokenType::NUM;
}

Pattern::TokenType Lexer::isIdentifier(string& s, int& tokLen) const {
    string id = "([a-zA-Z_]+)([a-zA-Z_0-9])*";
    std::regex pattern(id);

    tokLen = static_cast<int>(s.length());

    if (std::regex_match(s, pattern)) {
        return TokenType::ID;
    } else {
        return TokenType::NONE;
    }
}


/**
 * Creates a map defining which string keywords map to which tokens
 * @return map of keywords/tokens
 */
map<string, TokenType> Lexer::getKeywords() const {
    std::map<std::string, Pattern::TokenType> keywords {
            {"begin", TokenType::BEGIN},
            {"end", TokenType::END},
            {"program", TokenType::PROGRAM},
            {"procedure", TokenType::PROCEDURE},
            {"return", TokenType::RETURN},
            {"if", TokenType::IF},
            {"then", TokenType::THEN},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"print", TokenType::PRINT},
            {"println", TokenType::PRINTLN},
            {"var", TokenType::VAR},
            {"get", TokenType::GET},
            {"and", TokenType::AND},
            {"or", TokenType::OR},
            {"not", TokenType::NOT},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE}
    };

    return keywords;
}

const string &Lexer::getFileContent() const {
    return fileContent;
}

const std::vector<std::pair<TokenType, string>> &Lexer::getTokenList() const {
    return tokenList;
}

