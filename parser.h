#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "lexem.h"
#include "binTree.h"
#include "exitCodes.h"

const std::map<std::string, int> OPER = { {"-", 1}, {"+", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"sin", 4}, {"cos", 4}, {"ln", 4} };

Type getType(char c);
int getPriority(Lexem lex);
std::vector<Lexem> parse(const std::string& s);
bool comp(std::string oper1, std::string oper2);
std::vector<Lexem> getPostfixNotation(const std::vector<Lexem>& parsed);



