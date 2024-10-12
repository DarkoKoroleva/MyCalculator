#include "plugins.h"

void loadPlugins(std::map<std::string, FuncPtr>& functions) {
    WIN32_FIND_DATA findFileData;
    const wchar_t* fileName = L"plugins/*.dll"; //unicode
    HANDLE hFind = FindFirstFile(fileName, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No plugins found." << std::endl;
        return;
    }

    do {
        std::wstring fullPath = L"plugins/" + std::wstring(findFileData.cFileName);
        HMODULE hModule = LoadLibrary(fullPath.c_str());
        if (hModule) {
            FuncPtr func = (FuncPtr)GetProcAddress(hModule, "executeF"); // execute?
            FuncNamePtr nameFunc = (FuncNamePtr)GetProcAddress(hModule, "getNameF"); //getName?
            if (func && nameFunc) {
                functions.insert(std::make_pair(nameFunc(), func));
            }
            else {
                std::cerr << "Failed to load function from " << findFileData.cFileName << std::endl;
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
