#include "Parser.h"
using Pattern::TokenType;


Parser::Parser(const std::vector<Token>& toks) :
        tokens(removeComments(toks)),
        parseTree(parse())
{
}

void Parser::printTree() {

}

std::vector<Token> Parser::removeComments(std::vector<Token> tokens) {
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
        std::cout << "Matched " << type << std::endl;
    } else {
        std::string err = "Error: Invalid token " + type;
        err += " on line " + std::to_string(current.getLineNum());
        err += ", character " + std::to_string(current.getColNum());
        err += "\nExpected token " + Lexer::TOKEN_STRINGS[static_cast<unsigned long>(t)];
        std::cout << err.c_str() << std::endl;
        throw ParseException(err.c_str());
    }
}

TreeNode& Parser::parse() {
    try {
        prog(parseTree);
        return parseTree;
    } catch (ParseException e) {
        std::cout << e.what() << std::endl;
        exit(2);
    }
}

void Parser::prog(TreeNode& node) {
    node.setLabel("P");

    match(TokenType::PROGRAM, node);
    match(TokenType::ID, node);
    compound(node);
}

void Parser::compound(TreeNode &node) {
    TreeNode child("Compound");
    node.addChild(child);

    match(TokenType::BEGIN, child);
    stmt(child);
    stmts(child);
    match(TokenType::END, child);
}

void Parser::stmts(TreeNode &node) {
    TreeNode child("Stmts");
    node.addChild(child);

    TokenType t = tokens.front().getType();

    switch(t) {
        case TokenType::VAR:
        case TokenType::PRINT:
        case TokenType::PRINTLN:
        case TokenType::GET:
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
    TreeNode child("Stmt");
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
        case TokenType::ID:
            assign(child);
            break;
        default:
            std::string err = "Error: Invalid statement on line " + tokens.front().getLineNum();
            throw ParseException(err.c_str());
    }

}

void Parser::variable(TreeNode &node) {
    TreeNode child("V");
    node.addChild(child);

    match(TokenType::VAR, child);
    match(TokenType::ID, child);

    if (tokens.front().getType() == TokenType::ASSIGN) {
        variableAssign(child);
    }

    match(TokenType::SEMI, child);
}

void Parser::variableAssign(TreeNode &node) {
    TreeNode child("V'");
    node.addChild(child);

    match(TokenType::ASSIGN, child);
    expr(child);
}

void Parser::printStmt(TreeNode &node) {
    TreeNode child("Pr");
    node.addChild(child);

    TokenType t = tokens.front().getType();

    switch(t) {
        case TokenType::PRINT:
            match(TokenType::PRINT, child);
            expr(child);
            match(TokenType::SEMI, child);
            break;
        case TokenType::PRINTLN:
            match(TokenType::PRINTLN, child);
            expr(child);
            match(TokenType::SEMI, child);
            break;
        case TokenType::GET:
            match(TokenType::GET, child);
            match(TokenType::ID, child);
            match(TokenType::SEMI, child);
            break;
        default:
            std::string err = "Error: Invalid IO statement on line " + tokens.front().getLineNum();
            throw ParseException(err.c_str());
    }
}

void Parser::whileLoop(TreeNode &node) {
    TreeNode child("W");
    node.addChild(child);

    match(TokenType::WHILE, child);
    match(TokenType::LPAREN, child);
    orExpr1(child);
    match(TokenType::RPAREN, child);
    compound(child);
    match(TokenType::SEMI, child);
}

void Parser::ifStmt(TreeNode &node) {
    TreeNode child("I");
    node.addChild(child);

    match(TokenType::IF, child);
    match(TokenType::LPAREN, child);
    expr(child);
    match(TokenType::RPAREN, child);
    match(TokenType::THEN, child);
    compound(child);

    if (tokens.front().getType() == TokenType::ELSE) {
        elseStmt(child);
    }

    match(TokenType::SEMI, child);
}

void Parser::elseStmt(TreeNode &node) {
    TreeNode child("I'");
    node.addChild(child);

    match(TokenType::ELSE, child);
    compound(child);
}

void Parser::assign(TreeNode &node) {
    TreeNode child("A");
    node.addChild(child);

    match(TokenType::ID, child);
    match(TokenType::ASSIGN, child);
    expr(child);
    match(TokenType::SEMI, child);
}

void Parser::expr(TreeNode& node) {
    TreeNode child("expr");
    node.addChild(child);
    orExpr1(node);
}

void Parser::orExpr1(TreeNode &node) {
    andExpr1(node);
    orExpr2(node);
}

void Parser::orExpr2(TreeNode &node) {
    if (tokens.front().getType() == TokenType::OR) {
        match(TokenType::OR, node);
        andExpr1(node);
        orExpr2(node);
    }

}

void Parser::andExpr1(TreeNode &node) {
    equalsExpr1(node);
    andExpr2(node);
}

void Parser::andExpr2(TreeNode &node) {
    if (tokens.front().getType() == TokenType::AND) {
        match(TokenType::AND, node);
        equalsExpr1(node);
        andExpr2(node);
    }
}

void Parser::equalsExpr1(TreeNode &node) {
    relopExpr1(node);
    equalsExpr2(node);
}

void Parser::equalsExpr2(TreeNode &node) {
    if (tokens.front().getType() == TokenType::EQ) {
        match(TokenType::EQ, node);
        relopExpr1(node);
        equalsExpr2(node);
    }
}

void Parser::relopExpr1(TreeNode &node) {
    addExpr1(node);
    relopExpr2(node);
}

void Parser::relopExpr2(TreeNode &node) {
    switch(tokens.front().getType()) {
        case TokenType::LT:
            match(TokenType::LT, node);
            break;
        case TokenType::LTE:
            match(TokenType::LTE, node);
            break;
        case TokenType::GT:
            match(TokenType::GT, node);
            break;
        case TokenType::GTE:
            match(TokenType::GTE, node);
            break;
        default:
            return;
    }


    //Only executes if token is <, <=, >, >=
    addExpr1(node);
    relopExpr2(node);
}

void Parser::addExpr1(TreeNode &node) {
    mulExpr1(node);
    addExpr2(node);
}

void Parser::addExpr2(TreeNode &node) {
    TokenType t = tokens.front().getType();

    if (t == TokenType::PLUS) {
        match(TokenType::PLUS, node);
    } else if (t == TokenType::MINUS) {
        match(TokenType::MINUS, node);
    } else {
        return;
    }

    //Only executes if token is + or -
    mulExpr1(node);
    addExpr2(node);
}

void Parser::mulExpr1(TreeNode &node) {
    notExpr(node);
    mulExpr2(node);
}

void Parser::mulExpr2(TreeNode &node) {
    TokenType t = tokens.front().getType();

    if (t == TokenType::MULTIPLY) {
        match(TokenType::MULTIPLY, node);
    } else if (t == TokenType::DIVIDE) {
        match(TokenType::DIVIDE, node);
    } else {
        return;
    }

    //Only executes if token is * or /
    notExpr(node);
    mulExpr2(node);
}

void Parser::notExpr(TreeNode &node) {
    if (tokens.front().getType() == TokenType::NOT) {
        notExpr(node);
    }

    valueExpr(node);
}

void Parser::valueExpr(TreeNode &node) {
    Token t = tokens.front();

    switch(t.getType()) {
        case TokenType::LPAREN:
            match(TokenType::LPAREN, node);
            expr(node);
            match(TokenType::RPAREN, node);
            break;
        case TokenType::STRING:
            match(TokenType::STRING, node);
            break;
        case TokenType::NUM:
            match(TokenType::NUM, node);
            break;
        case TokenType::ID:
            match(TokenType::ID, node);
            break;
        case TokenType::TRUE:
            match(TokenType::TRUE, node);
            break;
        case TokenType::FALSE:
            match(TokenType::FALSE, node);
            break;
        default:
            std::string err = "Error: Invalid token " +
                    Lexer::TOKEN_STRINGS.at(static_cast<unsigned long>(t.getType()));
            err += " on line " + std::to_string(t.getLineNum());
            err += ", character " + std::to_string(t.getColNum());
            err += "\nExpected expression";
            throw ParseException(err.c_str());
    }
}

const std::vector<Token> &Parser::getTokens() const {
    return tokens;
}
