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
                std::cerr << "Invalid arithmetic expression";
                exit(-1);
            }

            std::unique_ptr<TreeNode> left;
            if (!stack.empty()) {
                left = std::move(stack.back());
                stack.pop_back();
            }
            else {
                std::cerr << "Invalid arithmetic expression";
                exit(-1);
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
                std::cerr << "Invalid arithmetic expression";
                exit(-1);
            }

            std::unique_ptr<TreeNode> node = std::make_unique<TreeNode>(lexem);
            node->left = nullptr;
            node->right = std::move(right);
            stack.push_back(std::move(node));
        }
    }

    return std::move(stack.back());
}

double evaluate(std::unique_ptr<TreeNode> top, std::map<std::string, FuncPtr> functions) {
    if (top.get()->value.type == Type::NUM) {
        try {
            return stod(top.get()->value.value);
        }
        catch (std::invalid_argument e) {
            std::cerr << e.what();
            exit(0);
        }
        catch (std::out_of_range e) {
            std::cerr << e.what();
            exit(0);
        }
    }
    else if (top.get()->value.type == Type::BIN_OPR) {
        std::vector<double> args = { evaluate(std::move(top.get()->left), functions), evaluate(std::move(top.get()->right), functions) };
        return functions[top.get()->value.value](args);
    }
    else if (top.get()->value.type == Type::UNA_OPR) {
        std::vector<double> args = {evaluate(std::move(top.get()->right), functions) };
        return functions[top.get()->value.value](args);
    }
}