//
// Created by locw on 11/10/19.
//

#include "Parser.h"
using Pattern::TokenType;


Parser::Parser(const std::vector<Token>& toks) :
        tokens(removeComments(toks)),
        parseTree(parse())
{
}

void Parser::printTree() {

}

std::vector<Token>& Parser::removeComments(const std::vector<Token>& tokens) {
    std::vector<Token> toks;

    for (Token t : tokens) {
        if (t.getType() != Pattern::TokenType::COMMENT)
            toks.emplace_back(t);
    }
    Lexer::printTokens(toks);
    return toks;
}

void Parser::match(TokenType t, TreeNode& node) {
    Token current = tokens.front();
    std::string type = Lexer::TOKEN_STRINGS.at(static_cast<unsigned long>(current.getType()));

    if (current.getType() == t) {
        node.addChild(TreeNode(type, current));
        tokens.erase(tokens.begin());
    } else {
        std::string err = "Error: Invalid token " + type;
        err += " on line " + current.getLineNum();
        err += ", character " + current.getColNum();
        err += "\nExpected token " + Lexer::TOKEN_STRINGS[static_cast<unsigned long>(t)];
        throw ParseException(err.c_str());
    }
}

TreeNode& Parser::parse() {
    return prog();
}

TreeNode& Parser::prog() {
    TreeNode node("prog");

    match(TokenType::PROGRAM, node);
    match(TokenType::ID, node);
    compound(node);
}

void Parser::compound(TreeNode &node) {
    TreeNode child("compound");
    node.addChild(child);

    match(TokenType::BEGIN, child);
    stmt(child);
    stmts(child);
    match(TokenType::END, child);
}

void Parser::stmts(TreeNode &node) {
    TreeNode child("stmts");
    node.addChild(child);

    TokenType t = tokens.front().getType();

    switch(t) {
        case TokenType::VAR:
        case TokenType::PRINT:
        case TokenType::PRINTLN:
        case TokenType::WHILE:
        case TokenType::IF:
        case TokenType::ASSIGN:
            stmt(child);
            stmts(child);
            break;
        default:
            break;
    }
}

void Parser::stmt(TreeNode &node) {
    TreeNode child("stmt");
    node.addChild(child);

    TokenType t = tokens.front().getType();

    switch (t) {
        case TokenType::VAR:
            variable(child);
            break;
        case TokenType::PRINT:
        case TokenType::PRINTLN:
        case TokenType::GET:    //Fall through is intentional
            printStmt(child);
            break;
        case TokenType::WHILE:
            whileLoop(child);
            break;
        case TokenType::IF:
            ifStmt(child);
            break;
        case TokenType::ASSIGN:
            assign(child);
            break;
        default:
            std::string err = "Error: Invalid statement on line " + tokens.front().getLineNum();
            throw ParseException(err.c_str());
    }

}

void Parser::variable(TreeNode &node) {
    TreeNode child("variable");
    node.addChild(child);

    match(TokenType::VAR, child);
    match(TokenType::ID, child);


    if (tokens.front().getType() == TokenType::ASSIGN) {
        variableAssign(child);
    }

    match(TokenType::SEMI, child);
}

void Parser::variableAssign(TreeNode &node) {
    TreeNode child("variableAssign");
    node.addChild(child);

    match(TokenType::ASSIGN, child);
    orExpr1(child);
}

void Parser::printStmt(TreeNode &node) {

}

void Parser::whileLoop(TreeNode &node) {

}

void Parser::ifStmt(TreeNode &node) {

}

void Parser::elseStmt(TreeNode &node) {

}

void Parser::assign(TreeNode &node) {

}

void Parser::orExpr1(TreeNode &node) {

}

void Parser::orExpr2(TreeNode &node) {

}

void Parser::andExpr1(TreeNode &node) {

}

void Parser::andExpr2(TreeNode &node) {

}

void Parser::equalsExpr1(TreeNode &node) {

}

void Parser::equalsExpr2(TreeNode &node) {

}

void Parser::relopExpr1(TreeNode &node) {

}

void Parser::relopExpr2(TreeNode &node) {

}

void Parser::addExpr1(TreeNode &node) {

}

void Parser::addExpr2(TreeNode &node) {

}

void Parser::mulExpr1(TreeNode &node) {

}

void Parser::mulExpr2(TreeNode &node) {

}

void Parser::notExpr(TreeNode &node) {

}

void Parser::bracketedExpr(TreeNode &node) {

}
