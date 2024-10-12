#include "pch.h"
#include "funcMultipl.h"
#include <memory>

double FuncMultipl::execute(const std::vector<double>& args) const {
    if (args.size() == 2) {
        return args[0] * args[1];
    }
    throw InvalidArgsException("command Multiply takes 2 arguments");
}

const char* FuncMultipl::getName() {
    return "*";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncMultipl>();
    return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncMultipl>();
    return strategy->getName();
}
