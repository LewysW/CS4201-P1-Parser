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

                if ((token = isKeyword(lexeme, tokLen, keywords)) != TokenType::NONE) {
                    tokens.emplace_back(std::make_pair(token, ""));
                } else if ((token = isNumeric(lexeme, tokLen)) != TokenType::NONE) {
                    tokens.emplace_back(std::make_pair(token, lexeme));
                }
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
    bool isReal = false;

    tokLen = static_cast<int>(s.length());

    //Checks for valid real or integer number
    for (char c : s) {
        if ((isReal && c =='.')) {
            return TokenType::NONE;
        } else if (!isReal && c == '.') {
            isReal = true;
        } else if (c < '0' || c > '9') {
            return TokenType::NONE;
        }
    }

    return isReal ? TokenType::REAL : TokenType::INT;
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

void Lexer::setFileContent(const string &fileContent) {
    Lexer::fileContent = fileContent;
}

