#pragma once

#include <vector>
#include "Token.h"

#include <memory>

class TreeNode {
private:
    std::vector<std::shared_ptr<TreeNode>> children;
    Token token;
    std::string label;

public:
    explicit TreeNode(std::string l);

    TreeNode(std::string l, Token t);

    const std::vector<std::shared_ptr<TreeNode>> &getChildren() const;

    void addChild(std::shared_ptr<TreeNode> child);

    void setLabel(const std::string &label);

    const Token &getToken() const;

};


