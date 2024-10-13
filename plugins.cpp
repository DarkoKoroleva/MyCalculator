#include "plugins.h"

void loadPlugins(std::map<std::string, FuncPtr>& functions) {
    WIN32_FIND_DATA findFileData;
    wchar_t currentPath[MAX_PATH]; //unicode
    GetCurrentDirectoryW(MAX_PATH, currentPath);

    std::wstring pluginPath = std::wstring(currentPath) + L"/plugins/*.dll";
    HANDLE hFind = FindFirstFile(pluginPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        //std::cerr << "No plugins found." << std::endl;
        throw std::runtime_error("No plugins found");
    }

    do {
        std::wstring fullPath = std::wstring(currentPath) + L"/plugins/" + std::wstring(findFileData.cFileName);
        HMODULE hModule = LoadLibrary(fullPath.c_str());
        if (hModule) {
            FuncPtr func = (FuncPtr)GetProcAddress(hModule, "executeF"); 
            FuncNamePtr nameFunc = (FuncNamePtr)GetProcAddress(hModule, "getNameF");
            if (func && nameFunc) {
                functions.insert(std::make_pair(nameFunc(), func));
            }
            else {
                //std::cerr << "Failed to load function from " << findFileData.cFileName << std::endl;
                throw std::runtime_error("Failed to load function");
            }
        }
        else {
            //std::cerr << "Failed to load library: " << fullPath.c_str() << std::endl;
            throw std::runtime_error("Failed to load library");
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
