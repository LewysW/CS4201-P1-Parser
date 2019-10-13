#pragma once

#include "TreeNode.h"
#include "Lexer.h"
#include <iostream>
#include <string>

class Parser {
private:
    //Current token counter
    std::vector<Token> tokens;
    std::shared_ptr<TreeNode> parseTree;
    std::vector<Token> removeComments(std::vector<Token> tokens);
    void printNode(std::shared_ptr<TreeNode> node);

    void match(Pattern::TokenType t, std::shared_ptr<TreeNode> node);

    void prog(std::shared_ptr<TreeNode> node); //P
    void compound(std::shared_ptr<TreeNode> node); //Compound
    void stmts(std::shared_ptr<TreeNode> node); //Stmts
    void stmt(std::shared_ptr<TreeNode> node); //Stmt
    void variable(std::shared_ptr<TreeNode> node); //V
    void variableAssign(std::shared_ptr<TreeNode> node); //V'
    void printStmt(std::shared_ptr<TreeNode> node); //Pr
    void whileLoop(std::shared_ptr<TreeNode> node); //W
    void ifStmt(std::shared_ptr<TreeNode> node); //I
    void elseStmt(std::shared_ptr<TreeNode> node); //I'
    void assign(std::shared_ptr<TreeNode> node); //A
    void expr(std::shared_ptr<TreeNode> node); //Added for readability in code, calls orExpr1
    void orExpr1(std::shared_ptr<TreeNode> node); //Expr1
    void orExpr2(std::shared_ptr<TreeNode> node); //Expr1'
    void andExpr1(std::shared_ptr<TreeNode> node); //Expr2
    void andExpr2(std::shared_ptr<TreeNode> node); //Expr2'
    void equalsExpr1(std::shared_ptr<TreeNode> node); //Expr3
    void equalsExpr2(std::shared_ptr<TreeNode> node); //Expr3'
    void relopExpr1(std::shared_ptr<TreeNode> node); //Expr4
    void relopExpr2(std::shared_ptr<TreeNode> node); //Expr4'
    void addExpr1(std::shared_ptr<TreeNode> node); //Expr5
    void addExpr2(std::shared_ptr<TreeNode> node); //Expr5'
    void mulExpr1(std::shared_ptr<TreeNode> node); //Expr6
    void mulExpr2(std::shared_ptr<TreeNode> node); //Expr6'
    void valueExpr(std::shared_ptr<TreeNode> node); //Expr7

public:
    explicit Parser(const std::vector<Token>& tokens);
    void parse();
    void printTree();

    const std::vector<Token> &getTokens() const;
};


