#include "binTree.h"

std::unique_ptr<TreeNode> buildTree(std::vector<Lexem>& lexems) {
    std::vector<std::unique_ptr<TreeNode>> stack;

    for (auto const& lexem : lexems) {
        if (lexem.type == Type::NUM) {
            stack.push_back(std::make_unique<TreeNode>(lexem));
        }
        else if (lexem.type == Type::BIN_OPR) {
            auto right = std::move(stack.back());
            stack.pop_back();
            auto left = std::move(stack.back());
            stack.pop_back();
            auto node = std::make_unique<TreeNode>(lexem);
            node->left = std::move(left);
            node->right = std::move(right);
            stack.push_back(std::move(node));
        }
        else if (lexem.type == Type::UNA_OPR) {
            auto right = std::move(stack.back());
            stack.pop_back();
            auto node = std::make_unique<TreeNode>(lexem);
            node->left = nullptr;
            node->right = std::move(right);
            stack.push_back(std::move(node));
        }
    }

    return std::move(stack.back());
}