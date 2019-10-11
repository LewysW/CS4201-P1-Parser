//
// Created by locw on 11/10/19.
//

#include "Parser.h"

Parser::Parser(std::vector<Token> const &tokens) :
        parseTree((parse(tokens)))
{
}

void Parser::printTree() {

}

TreeNode Parser::parse(std::vector<Token> const& tokens) {
    Lexer::printTokens(tokens);
    TreeNode node("hello");
    return node;
}