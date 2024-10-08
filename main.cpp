#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <set>

/*typedef double (*FuncPtr)(double);
typedef const char* (*FuncNamePtr)();

void loadPlugins(std::vector<FuncPtr>& functions, std::vector<std::string>& names) {
    WIN32_FIND_DATA findFileData;
    LPCTSTR fileName = "plugins/*.dll";
    HANDLE hFind = FindFirstFile("plugins/*.dll", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No plugins found." << std::endl;
        return;
    }

    do {
        HMODULE hModule = LoadLibrary(findFileData.cFileName);
        if (hModule) {
            FuncPtr func = (FuncPtr)GetProcAddress(hModule, "function"); // Замените на правильное имя
            FuncNamePtr nameFunc = (FuncNamePtr)GetProcAddress(hModule, "getFunctionName");
            if (func && nameFunc) {
                functions.push_back(func);
                names.push_back(nameFunc());
            }
            else {
                std::cerr << "Failed to load function from " << findFileData.cFileName << std::endl;
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}*/

enum Type {
    NUM,
    OPR,
    BRC
};

struct Lexem {
public:
    Type type;
    std::string value;

    Lexem(Type type, std::string value) {
        this->type = type;
        this->value = value;
    }
};

Type getType(char c) {
    std::string num = "0123456789.";
    std::string oper = "+-*/, sin, cos, ln, !";
    std::string brc = "()";

    if (num.find(c) != std::string::npos) {
        return Type::NUM;
    }
    else if (oper.find(c) != std::string::npos) {
        return Type::OPR;
    }
    else if (brc.find(c) != std::string::npos) {
        return Type::BRC;
    }
    else {
        std::cerr << "unrecognized char" + c;
        exit(0);
    }
    //unrecognized char??
}

std::vector<Lexem> parse(const std::string& s) {
    std::set<std::string> operation = { "sin", "cos", "ln", "!", "+", "-", "*", "/" };
    std::vector<Lexem> parsed;
    std::string lexem;
    int counterBrc = 0;

    //std::string::iterator it;
    for (int it = 0; it < s.size() - 1; it++) {
        if (s[it] == '(') {
            counterBrc++;
        }
        else if (s[it] == ')') {
            counterBrc--;
            if (counterBrc < 0) {
                std::cerr << "invalid arithmetic expression";
                exit(0);
            }
        }

        if (getType(s[it]) == getType(s[it + 1])) {
            lexem += s[it];
        }
        else {
            lexem += s[it];
            if (getType(s[it]) == Type::OPR && operation.find(lexem) == operation.end()) {
                std::cerr << "No such operator '" + lexem + "'";
                exit(0);
            }
            parsed.emplace_back(getType(s[it]), lexem);
            lexem.clear();
        }
    }
    int it = s.size() - 1;
    if (s[it] == '(') counterBrc++;
    else if (s[it] == ')') counterBrc--;

    lexem += s[it];
    parsed.emplace_back(getType(s[s.size()-1]), lexem);
    lexem.clear();

    if (counterBrc != 0) {
        std::cerr << "invalid arithmetic expression";
        exit(0);
    }
    return parsed;
}

int main() {
    //std::vector<FuncPtr> functions;
    //std::vector<std::string> names;

    //loadPlugins(functions, names);

    // Здесь добавьте код для парсинга выражений и вычислений
    std::string s = "12.0+1*2*12.24-0";
    parse(s);

    return 0;
}
