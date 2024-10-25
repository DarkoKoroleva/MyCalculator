#include "binTree.h"

std::unique_ptr<TreeNode> buildTree(std::vector<Lexem>& lexems) {
    std::vector<std::unique_ptr<TreeNode>> stack;

    for (auto const& lexem : lexems) {
        if (lexem.type == Type::NUM) {
            stack.push_back(std::make_unique<TreeNode>(lexem));
        }
        else if (lexem.type == Type::BIN_OPR) {

            std::unique_ptr<TreeNode> right;
            if (!stack.empty()) {
                right = std::move(stack.back());
                stack.pop_back();
            }
            else {
                throw std::runtime_error("Invalid arithmetic expression");
            }

            std::unique_ptr<TreeNode> left;
            if (!stack.empty()) {
                left = std::move(stack.back());
                stack.pop_back();
            }
            else {
                throw std::runtime_error("Invalid arithmetic expression");
            }

            std::unique_ptr<TreeNode> node = std::make_unique<TreeNode>(lexem);
            node->left = std::move(left);
            node->right = std::move(right);
            stack.push_back(std::move(node));
        }
        else if (lexem.type == Type::UNA_OPR) {

            std::unique_ptr<TreeNode> right;
            if (!stack.empty()) {
                right = std::move(stack.back());
                stack.pop_back();
            }
            else {
                throw std::runtime_error("Invalid arithmetic expression");
            }

            std::unique_ptr<TreeNode> node = std::make_unique<TreeNode>(lexem);
            node->left = nullptr;
            node->right = std::move(right);
            stack.push_back(std::move(node));
        }
    }

    return std::move(stack.back());
}

double evaluate(const std::unique_ptr<TreeNode> top, const std::map<std::string, FuncPtr>& functions) {
    if (top->value.type == Type::NUM) {
        try {
            return stod(top->value.value);
        }
        catch (std::invalid_argument e) {
            throw std::runtime_error(e.what());
        }
        catch (std::out_of_range e) {
            throw std::runtime_error(e.what());
        }
    }
    else if (top->value.type == Type::BIN_OPR) {
        double left = evaluate(std::move(top->left), functions);
        double right = evaluate(std::move(top->right), functions);
        std::vector<double> args = { left, right};
        return functions.at(top->value.value)(args);
    }
    else if (top->value.type == Type::UNA_OPR) {
        std::vector<double> args = {evaluate(std::move(top->right), functions) };
        return functions.at(top->value.value)(args);
    }

    throw std::runtime_error("Unknown node type");
}