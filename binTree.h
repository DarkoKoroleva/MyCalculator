#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "lexem.h"

struct TreeNode {
    Lexem value;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

    TreeNode(const Lexem val) : value(val), left(nullptr), right(nullptr) {}
};


std::unique_ptr<TreeNode> buildTree(std::vector<Lexem>& lexems);
