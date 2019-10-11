#pragma once

#include "TreeNode.h"
#include "Lexer.h"
#include <iostream>
#include <string>

class Parser {
private:
    TreeNode parseTree;

public:
    explicit Parser(std::vector<Token> const& tokens);
    TreeNode parse(std::vector<Token> const& tokens);
    void printTree();
};


