//
// Created by locw on 11/10/19.
//

#include "TreeNode.h"

TreeNode::TreeNode(std::string l)  :
        label(std::move(l))
{
}

TreeNode::TreeNode(std::string l, Token t)  :
        label(std::move(l)),
        token(std::move(t))
{
}

const std::vector<TreeNode> &TreeNode::getChildren() const {
    return children;
}

void TreeNode::addChild(const TreeNode &child) {
    children.emplace_back(child);
}