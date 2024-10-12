#include "pch.h" 
#include "funcAdd.h"

double FuncAdd::execute(const std::vector<double>& args) const {
	if (args.size() == 2) {
		return args[0] + args[1];
	}
	else {
		throw InvalidArgsException("command Add takes 2 arguments");
	}
}

const char* FuncAdd::getName() {
	return "+";
}

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args) {
	std::unique_ptr<Strategy> strategy = std::make_unique<FuncAdd>();
	return strategy->execute(args);
}

extern "C" __declspec(dllexport) const char* getNameF() {
	std::unique_ptr<Strategy> strategy = std::make_unique<FuncAdd>();
	return strategy->getName();
}