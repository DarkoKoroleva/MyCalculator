#pragma once
#include <windows.h>
#include "../../include/strategy.h"
#include"../../include/invalidArgsException.h"

class FuncSub : public Strategy {
public:
    double execute(const std::vector<double>& args) const override;

    const char* getName() override;
};

extern "C" __declspec(dllexport) double executeF(const std::vector<double>&args);
extern "C" __declspec(dllexport) const char* getNameF();



