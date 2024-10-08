#include "pch.h" 
#include "funcSin.h"

class FuncSin : public Strategy {
public:
    double execute(const std::vector<double>& args) const override {
        if (args.size() == 1) {
            return sin(args[0]);
        }
        throw InvalidArgsException("command Sin takes 1 argument");
    }

    const char* getName() override {
        return "sin";
    }
};

Strategy * create() {
    return new FuncSin();
}
