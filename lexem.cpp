#include <string>
#include "lexem.h"

Lexem ::Lexem(Type type, std::string value) {
    this->type = type;
    this->value = value;
}