#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "lexem.h"
#include "plugins.h"

struct TreeNode {
    Lexem value;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(const Lexem val) : value(val), left(nullptr), right(nullptr) {}
};


std::unique_ptr<TreeNode> buildTree(std::vector<Lexem>& lexems);
double evaluate(const std::unique_ptr<TreeNode> top, const std::map<std::string, FuncPtr>& functions);
