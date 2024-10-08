#include "../plugins/funcSin/pch.h"
#include "invalidArgsException.h"

InvalidArgsException::InvalidArgsException(std::string message) : message{ message } {}

std::string InvalidArgsException::getMessage() const {
    return message;
}