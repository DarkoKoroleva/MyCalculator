#include "pch.h"
#include "funcSub.h"
#include <memory>

double FuncSub::execute(const std::vector<double>& args) const {
    if (args.size() == 1) {
        return -args[0];
    }
    else if (args.size() == 2) {
        return args[0] - args[1];
    }
    throw InvalidArgsException("command Subtract takes 1 or 2 arguments");
}

const char* FuncSub::getName() {
    return "-";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncSub>();
    return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncSub>();
    return strategy->getName();
}