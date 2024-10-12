#include "pch.h" 
#include "funcSin.h"
#include <memory>

double FuncSin::execute(const std::vector<double>& args) const {
    if (args.size() == 1) {
        return sin(args[0]);
    }
    throw InvalidArgsException("command Sin takes 1 argument");
}

const char* FuncSin::getName() {
	return "sin";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
	std::unique_ptr<Strategy> strategy = std::make_unique<FuncSin>();
	return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
	std::unique_ptr<Strategy> strategy = std::make_unique<FuncSin>();
	return strategy->getName();
}