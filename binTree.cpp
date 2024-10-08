#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "lexem.cpp"

struct TreeNode {
    std::string value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};


std::shared_ptr<TreeNode> buildTree(std::vector<Lexem>& lexems) {
    std::vector<std::shared_ptr<TreeNode>> stack;

    for (auto const& lexem : lexems) {
        if (lexem.type == Type::NUM) {
            stack.push_back(std::make_shared<TreeNode>(lexem));
        }
        else if (lexem.type == Type::OPR) {
            auto right = stack.back(); 
            stack.pop_back();
            auto left = stack.back(); 
            stack.pop_back();
            auto node = std::make_shared<TreeNode>(lexem);
            node->left = left;
            node->right = right;
            stack.push_back(node);
        }
    }

    return stack.back();
}