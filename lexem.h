#pragma once

#include <string>
enum class Type {
    NUM,
    OPR,
    BIN_OPR,
    UNA_OPR,
    BRC
};

struct Lexem {
public:
    Type type;
    std::string value;

    Lexem(Type type, std::string value);
};
