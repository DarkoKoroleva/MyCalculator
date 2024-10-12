#include "pch.h"
#include "funcDeg.h"
#include <memory>
double FuncDeg::execute(const std::vector<double>& args) const {
    if (args.size() == 2) {
        return pow(args[0], args[1]);
    }
    throw InvalidArgsException("command Degree takes 2 arguments");
}

const char* FuncDeg::getName() {
    return "^";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncDeg>();
    return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncDeg>();
    return strategy->getName();
}