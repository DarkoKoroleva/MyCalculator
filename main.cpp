#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include "parser.h"
#include "plugins.h"
#include "binTree.h"
#include "lexem.h"
#include "include/invalidArgsException.h"

int main() {
    std::map<std::string, FuncPtr> functions;

    try {
        loadPlugins(functions);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        std::cout << "Have a good day!" << std::endl;
        system("pause");
        return 0;
    }
    

    std::string input;
    //std::string s = "sin(-ln1.0+2*(-2.5/2+2))^2+cos(-ln1.0+2*(-2.5/2+2))^2";
    while (true) {
        try {
            std::cin >> input;
            if (input == "exit") {
                std::cout << "Have a good day!" << std::endl;
                system("pause");
                return 0;
            }
            std::vector<Lexem> lexems = parse(input);
            std::vector<Lexem> postLexems = getPostfixNotation(lexems);

            std::unique_ptr<TreeNode> top = buildTree(postLexems);
            double result = evaluate(top, functions);

            std::cout << result << std::endl;
        }
        catch (std::runtime_error e) {
            std::cerr << e.what() << std::endl;
        }
        catch (InvalidArgsException e) {
            std::cerr << e.getMessage() << std::endl;
        }
    }
}
