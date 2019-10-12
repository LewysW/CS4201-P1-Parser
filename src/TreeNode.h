#pragma once

#include <vector>
#include "Token.h"

class TreeNode {
private:
    std::vector<TreeNode> children;
    Token token;
    std::string label;

public:
    explicit TreeNode(std::string l);

    TreeNode(std::string l, Token t);

    const std::vector<TreeNode> &getChildren() const;

    void addChild(const TreeNode &child);

    void setLabel(const std::string &label);

    const std::string &getLabel() const;

};


