#include <iostream>

#include "gitutil.h"

int main() {
    GitUtil util;
    std::cout << util.getVersion() << std::endl;
    return 0;
}
