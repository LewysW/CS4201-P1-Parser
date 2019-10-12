#include "TreeNode.h"

TreeNode::TreeNode(std::string l)  :
        label(std::move(l)),
        token(Token(Pattern::TokenType::NONE, l, 0, 0))
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

void TreeNode::setLabel(const std::string &label) {
    TreeNode::label = label;
}

const std::string &TreeNode::getLabel() const {
    return label;
}

const Token &TreeNode::getToken() const {
    return token;
}
