#include "parser.h"

Type getType(char c) {
    std::string num = "0123456789.";//make global?
    std::string binOper = "+-*/^";
    std::string unaOper = "sin, cos, ln, !";
    std::string brc = "()";

    if (num.find(c) != std::string::npos) {
        return Type::NUM;
    }
    else if (binOper.find(c) != std::string::npos) {
        return Type::BIN_OPR;
    }
    else if (unaOper.find(c) != std::string::npos) {
        return Type::UNA_OPR;
    }
    else if (brc.find(c) != std::string::npos) {
        return Type::BRC;
    }
    else {
        std::string invalidChar{ c };
        std::cerr << "unrecognized char '" + invalidChar +"'";
        exit(0);
    }
}

std::vector<Lexem> parse(const std::string& s) {
    std::set<std::string> unaOper = { "sin", "cos", "ln", "!" };
    std::vector<Lexem> parsed;
    std::string lexem;
    int counterBrc = 0;

    for (int it = 0; it < s.size() - 1; it++) {
        if (s[it] == '(') {
            counterBrc++;
            parsed.emplace_back(Type::BRC, "(");
            continue;
        }
        else if (s[it] == ')') {
            counterBrc--;
            if (counterBrc < 0) {
                std::cerr << "invalid arithmetic expression";
                exit(0);
            }
            parsed.emplace_back(Type::BRC, ")");
            continue;
        }
        Type currType = getType(s[it]);

        if (currType == getType(s[it + 1])) {
            lexem += s[it];
        }
        else {
            lexem += s[it];
            if (lexem == "-" && (it == 0 || s[it - 1] == '(')) { //unary minus
                currType = Type::UNA_OPR;
            }
            else if (currType == Type::UNA_OPR && unaOper.find(lexem) == unaOper.end()) {
                std::cerr << "No such operator '" + lexem + "'";
                exit(0);
            }
            parsed.emplace_back(currType, lexem);
            lexem.clear();
        }
    }

    int it = s.size() - 1;
    if (s[it] == '(') counterBrc++;
    else if (s[it] == ')') counterBrc--;

    lexem += s[it];
    parsed.emplace_back(getType(s[s.size() - 1]), lexem);
    lexem.clear();

    if (counterBrc != 0) {
        std::cerr << "invalid arithmetic expression";
        exit(0);
    }
    return parsed;
}


bool comp(std::string oper1, std::string oper2) {
    return OPER.at(oper1) < OPER.at(oper2);
}

int getPriority(Lexem lex) {
    if (lex.type == Type::NUM) {
        return 0;
    }
    else if (lex.type == Type::BIN_OPR || lex.type == Type::UNA_OPR) {
        return OPER.at(lex.value);
    }
}

std::vector<Lexem> getPostfixNotation(const std::vector<Lexem>& parsed) {
    std::stack<Lexem> stack;
    std::vector<Lexem> postfix;
    std::vector<Lexem>::iterator it;
    for (Lexem it : parsed) {

        if (it.type == Type::BRC) {
            if (it.value == "(") {
                stack.push(it);
            }
            else if (it.value == ")") {
                while (!stack.empty() && stack.top().value != "(") {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty()) {
                    stack.pop(); //'('
                }
            }
        }
        else if (it.type == Type::NUM) {
            postfix.push_back(it);
        }
        else { //operator
            if (stack.empty()) {
                stack.push(it);
            }
            else {
                while (!stack.empty() && getPriority(it) <= getPriority(stack.top()) && stack.top().value != "(") {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                stack.push(it);
            }
        }
    }
    while (!stack.empty()) {
        postfix.push_back(stack.top());
        stack.pop();
    }
    return postfix;
}


