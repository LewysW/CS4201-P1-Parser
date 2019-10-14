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

void TreeNode::addChild(std::shared_ptr<TreeNode> child) {
    children.emplace_back(child);
}

void TreeNode::setLabel(const std::string &label) {
    TreeNode::label = label;
}

const Token &TreeNode::getToken() const {
    return token;
}

const std::vector<std::shared_ptr<TreeNode>> &TreeNode::getChildren() const {
    return children;
}
