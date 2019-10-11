#pragma once

#include "TreeNode.h"
#include "Lexer.h"
#include <iostream>
#include <string>

class Parser {
private:
    //Current token counter
    std::vector<Token>& tokens;
    TreeNode parseTree;
    std::vector<Token>& removeComments(const std::vector<Token>& tokens);

    void match(Pattern::TokenType t, TreeNode& node);

    TreeNode& prog(); //P
    void compound(TreeNode& node); //Compound
    void stmts(TreeNode& node); //Stmts
    void stmt(TreeNode& node); //Stmt
    void variable(TreeNode& node); //V
    void variableAssign(TreeNode& node); //V'
    void printStmt(TreeNode& node); //Pr
    void whileLoop(TreeNode& node); //W
    void ifStmt(TreeNode& node); //I
    void elseStmt(TreeNode& node); //I'
    void assign(TreeNode& node); //A
    void orExpr1(TreeNode& node); //Expr1
    void orExpr2(TreeNode& node); //Expr1'
    void andExpr1(TreeNode& node); //Expr2
    void andExpr2(TreeNode& node); //Expr2'
    void equalsExpr1(TreeNode& node); //Expr3
    void equalsExpr2(TreeNode& node); //Expr3'
    void relopExpr1(TreeNode& node); //Expr4
    void relopExpr2(TreeNode& node); //Expr4'
    void addExpr1(TreeNode& node); //Expr5
    void addExpr2(TreeNode& node); //Expr5'
    void mulExpr1(TreeNode& node); //Expr6
    void mulExpr2(TreeNode& node); //Expr6'
    void notExpr(TreeNode& node); //Expr7
    void bracketedExpr(TreeNode& node); //Expr8

public:
    explicit Parser(const std::vector<Token>& tokens);
    TreeNode& parse();
    void printTree();
};


