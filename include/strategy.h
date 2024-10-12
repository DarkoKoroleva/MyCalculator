#pragma once
#pragma warning(disable : 4996)
#include <vector>

class Strategy {
public:
	virtual double execute(const std::vector<double>& args) const = 0;
	virtual const char* getName() = 0;
};