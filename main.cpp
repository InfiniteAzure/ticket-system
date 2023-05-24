#include <iostream>
#include "bplus.h"
#include "users.h"
#include "processor.h"

int main() {
    std::string op;
    User_system user_system;
    while(std::getline(std::cin, op)) {
        processor s(op);
        if (s.words[1] == "add_user") {
            int i = 2;
            while ()
        }
    }

    return 0;
}
