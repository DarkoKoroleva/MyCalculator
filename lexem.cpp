#include <string>
enum Type {
    NUM,
    OPR,
    BRC
};

struct Lexem {
public:
    Type type;
    std::string value;

    Lexem(Type type, std::string value) {
        this->type = type;
        this->value = value;
    }
};