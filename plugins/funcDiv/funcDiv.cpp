#include "pch.h" 
#include "funcDiv.h"
#include <memory>

double FuncDiv::execute(const std::vector<double>& args) const {
    if (args.size() == 2) {
        if (args[1] == 0) throw InvalidArgsException("you shouldn't divide by 0");
        return args[0] / args[1];
    }
    throw InvalidArgsException("command division takes 2 argument");
}

const char* FuncDiv::getName() {
    return "/";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncDiv>();
    return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncDiv>();
    return strategy->getName();
}
