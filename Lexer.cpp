#include <iostream>
#include <fstream>
#include "Lexer.h"

using Pattern::TokenType;
using std::string;
using std::regex;

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
    std::vector<std::pair<TokenType, string>> symbols = match(false);
    std::vector<std::pair<TokenType, string>> identifiers = match(true);
    std::vector<std::pair<TokenType, string>> tokens;

    int index = 0;
    for (std::pair<TokenType, string> & p : identifiers) {
        if (p.second == symbols[index].second) {
            tokens.emplace_back(symbols[index]);
            index++;
        } else {
            tokens.emplace_back(p);
        }

        std::cout << TOKEN_STRINGS[static_cast<int>(tokens.back().first)] << ": " << tokens.back().second << std::endl;
    }

    return tokens;
}

/**
 * Uses regex iterator to match a map of tokens with the content of the provided file
 * @param matchID - whether to match identifiers
 * @return list of tokens idenfitifed using regex
 */
std::vector<std::pair<TokenType, string>> Lexer::match(bool matchID) const {
    std::map<TokenType, string> regPatterns = createTokenMap();

    /**
     * https://stackoverflow.com/questions/34229328/writing-a-very-simple-lexical-analyser-in-c
     */
    std::map<size_t, std::pair<string, TokenType>> matches;
    std::vector<std::pair<TokenType, string>> tokens;


    //Iterates over each pattern in the list of regex patterns
    for (auto pat = regPatterns.begin(); pat != regPatterns.end(); ++pat) {
        if (pat->first != TokenType::ID || matchID) {
            //Initialises a regex object with the extended regex to ensure the correct behaviour
            regex r(pat->second, regex::extended);

            //Initialises a regex iterator which identifies the valid tokens of the current pattern
            auto words_begin = std::sregex_iterator(getFileContent().begin(), getFileContent().end(), r);
            auto words_end = std::sregex_iterator();

            //Adds all of the valid tokens of the current pattern to the map
            for (auto it = words_begin; it != words_end; ++it) {
                matches[it->position()] = std::make_pair(it->str(), pat->first);
            }
        }
    }

    //Assigns tokens to vector
    for (auto token = matches.begin(); token != matches.end(); token++) {
        tokens.emplace_back(std::make_pair(token->second.second, token->second.first));
        //std::cout << TOKEN_STRINGS[static_cast<int>(tokens.back().first)] << ": " << tokens.back().second << std::endl;
    }

    return tokens;
}

/**
 * Creates a map defining the tokens to be lexed and their corresponding regex
 * @return map of tokens/regex
 */
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
}

const string &Lexer::getFileContent() const {
    return fileContent;
}

void Lexer::setFileContent(const string &fileContent) {
    Lexer::fileContent = fileContent;
}

