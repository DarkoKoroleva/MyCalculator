#pragma once
#include <string>

class InvalidArgsException : public std::exception {
public:
    InvalidArgsException(std::string message);
    std::string getMessage() const;
private:
    std::string message;
};
