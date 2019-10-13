#include "Parser.h"
using Pattern::TokenType;


Parser::Parser(const std::vector<Token>& toks) :
        tokens(removeComments(toks)),
        parseTree(std::make_shared<TreeNode>(TreeNode("P")))
{
    parse();
}

void Parser::printTree() {
    std::cout << "Syntactic Analysis:" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    printNode(parseTree);
}

//TODO - the printing
//TODO - use static variable for tabs
void Parser::printNode(std::shared_ptr<TreeNode> node) {
    Token const& token = node->getToken();
    static std::string tabStr;

    if (token.getType() != TokenType::NONE) {
        std::string tokStr = "\"" + Lexer::TOKEN_STRINGS.at(static_cast<unsigned long>(token.getType())) + "\"";
        tokStr += ((token.getValue().empty()) ? "" : (": \"" + token.getValue() + "\"")) ;
        std::cout << tabStr << tokStr << std::endl;
    } else {
        std::cout << tabStr << token.getValue() << " {" << std::endl;
        tabStr += "\t";
        for (const std::shared_ptr<TreeNode>& t : node->getChildren()) {
            printNode(t);
        }

        if (tabStr.length() > 0) {
            tabStr.erase(tabStr.length() - 1);
        }

        std::cout << tabStr << std::endl << "}" << std::endl;
    }
}

std::vector<Token> Parser::removeComments(std::vector<Token> tokens) {
    std::vector<Token> toks;

    for (Token t : tokens) {
        if (t.getType() != Pattern::TokenType::COMMENT)
            toks.emplace_back(t);
    }

    return toks;
}

void Parser::match(TokenType t, std::shared_ptr<TreeNode> node) {
    Token current = tokens.front();
    std::string type = Lexer::TOKEN_STRINGS.at(static_cast<unsigned long>(current.getType()));

    if (current.getType() == t) {
        TreeNode child(type, current);
        node->addChild(std::make_shared<TreeNode>(child));
        tokens.erase(tokens.begin());
    } else {
        std::string err = "Error: Invalid token \'" + type;
        err += "\' on line " + std::to_string(current.getLineNum());
        err += ", character " + std::to_string(current.getColNum());
        err += ". Expected token \'" + Lexer::TOKEN_STRINGS[static_cast<unsigned long>(t)];
        err += "\'";
        std::cout << err.c_str() << std::endl;
        throw ParseException(err.c_str());
    }
}

void Parser::parse() {
    try {
        prog(parseTree);
    } catch (ParseException& e) {
        std::cout << e.what() << std::endl;
        exit(2);
    }
}

void Parser::prog(std::shared_ptr<TreeNode> node) {
    node->setLabel("P");

    match(TokenType::PROGRAM, node);
    match(TokenType::ID, node);
    compound(node);
}

void Parser::compound(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("Compound"));
    node->addChild(child);

    match(TokenType::BEGIN, child);
    stmt(child);
    stmts(child);
    match(TokenType::END, child);
}

void Parser::stmts(std::shared_ptr<TreeNode> node) {
    TokenType t = tokens.front().getType();

    switch(t) {
        case TokenType::VAR:
        case TokenType::PRINT:
        case TokenType::PRINTLN:
        case TokenType::GET:
        case TokenType::WHILE:
        case TokenType::IF:
        case TokenType::ID:
            stmt(node);
            stmts(node);
            break;
        default:
            break;
    }
}

void Parser::stmt(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("Stmt"));
    node->addChild(child);

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

void Parser::variable(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("V"));
    node->addChild(child);

    match(TokenType::VAR, child);
    match(TokenType::ID, child);

    if (tokens.front().getType() == TokenType::ASSIGN) {
        variableAssign(child);
    }

    match(TokenType::SEMI, child);
}

void Parser::variableAssign(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("V'"));
    node->addChild(child);

    match(TokenType::ASSIGN, child);
    expr(child);
}

void Parser::printStmt(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("Pr"));
    node->addChild(child);

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

void Parser::whileLoop(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("W"));
    node->addChild(child);

    match(TokenType::WHILE, child);
    match(TokenType::LPAREN, child);
    orExpr1(child);
    match(TokenType::RPAREN, child);
    compound(child);
    match(TokenType::SEMI, child);
}

void Parser::ifStmt(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("I"));
    node->addChild(child);

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

void Parser::elseStmt(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("I'"));
    node->addChild(child);

    match(TokenType::ELSE, child);
    compound(child);
}

void Parser::assign(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("A"));
    node->addChild(child);

    match(TokenType::ID, child);
    match(TokenType::ASSIGN, child);
    expr(child);
    match(TokenType::SEMI, child);
}

void Parser::expr(std::shared_ptr<TreeNode> node) {
    std::shared_ptr<TreeNode> child = std::make_shared<TreeNode>(TreeNode("expr"));
    node->addChild(child);
    orExpr1(node);
}

void Parser::orExpr1(std::shared_ptr<TreeNode> node) {
    andExpr1(node);
    orExpr2(node);
}

void Parser::orExpr2(std::shared_ptr<TreeNode> node) {
    if (tokens.front().getType() == TokenType::OR) {
        match(TokenType::OR, node);
        andExpr1(node);
        orExpr2(node);
    }

}

void Parser::andExpr1(std::shared_ptr<TreeNode> node) {
    equalsExpr1(node);
    andExpr2(node);
}

void Parser::andExpr2(std::shared_ptr<TreeNode> node) {
    if (tokens.front().getType() == TokenType::AND) {
        match(TokenType::AND, node);
        equalsExpr1(node);
        andExpr2(node);
    }
}

void Parser::equalsExpr1(std::shared_ptr<TreeNode> node) {
    relopExpr1(node);
    equalsExpr2(node);
}

void Parser::equalsExpr2(std::shared_ptr<TreeNode> node) {
    if (tokens.front().getType() == TokenType::EQ) {
        match(TokenType::EQ, node);
        relopExpr1(node);
        equalsExpr2(node);
    }
}

void Parser::relopExpr1(std::shared_ptr<TreeNode> node) {
    addExpr1(node);
    relopExpr2(node);
}

void Parser::relopExpr2(std::shared_ptr<TreeNode> node) {
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

void Parser::addExpr1(std::shared_ptr<TreeNode> node) {
    mulExpr1(node);
    addExpr2(node);
}

void Parser::addExpr2(std::shared_ptr<TreeNode> node) {
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

void Parser::mulExpr1(std::shared_ptr<TreeNode> node) {
    valueExpr(node);
    mulExpr2(node);
}

void Parser::mulExpr2(std::shared_ptr<TreeNode> node) {
    TokenType t = tokens.front().getType();

    if (t == TokenType::MULTIPLY) {
        match(TokenType::MULTIPLY, node);
    } else if (t == TokenType::DIVIDE) {
        match(TokenType::DIVIDE, node);
    } else {
        return;
    }

    //Only executes if token is * or /
    valueExpr(node);
    mulExpr2(node);
}

void Parser::valueExpr(std::shared_ptr<TreeNode> node) {
    Token t = tokens.front();

    switch(t.getType()) {
        case TokenType::NOT:
            match(TokenType::NOT, node);
            valueExpr(node);
            break;
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
