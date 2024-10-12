#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>

typedef double (*FuncPtr)(const std::vector<double>&);
typedef const char* (*FuncNamePtr)();

void loadPlugins(std::map<std::string, FuncPtr>& functions);
