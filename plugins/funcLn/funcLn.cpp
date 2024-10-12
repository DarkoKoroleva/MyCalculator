#include "pch.h" 
#include "funcLn.h"
#include <memory>

double FuncLn::execute(const std::vector<double>& args) const {
	if (args.size() == 1) {
		if (args[0] <= 0) throw InvalidArgsException("command ln takes a positive argument");
		return log(args[0]);
	}

	throw InvalidArgsException("command ln takes 1 argument");
}

const char* FuncLn::getName() {
    return "ln";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncLn>();
    return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
    std::unique_ptr<Strategy> strategy = std::make_unique<FuncLn>();
    return strategy->getName();
}