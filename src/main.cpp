#include <iostream>

#include "gitutil.h"

int main() {
    std::cout << GitUtil::getVersion() << std::endl;
    return 0;
}
