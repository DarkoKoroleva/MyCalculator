#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include "parser.h"
#include "plugins.h"
#include "binTree.h"
#include "lexem.h"

int main() {
    std::map<std::string, FuncPtr> functions;

    loadPlugins(functions);

    try {
        std::string s = "sin(-ln1.0+2*(-2.5/2+2))^2+cos(-ln1.0+2*(-2.5/2+2))^2";
        std::vector<Lexem> lexems = parse(s);
        std::vector<Lexem> postLexems = getPostfixNotation(lexems);
    
        std::unique_ptr<TreeNode> top = buildTree(postLexems);
        double result = evaluate(std::move(top), functions);

        std::cout << result;
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
