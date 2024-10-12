#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>
#include "../../include/strategy.h"
#include"../../include/invalidArgsException.h"

class FuncSin : public Strategy {
public:
    double execute(const std::vector<double>& args) const override;

    const char* getName() override;
};

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args);
extern "C" __declspec(dllexport) const char* getNameF();

