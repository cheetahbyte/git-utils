#include <iostream>

#include "gitutil.h"

int main() {
    const auto commits = GitUtil::getCommits();
    for (const auto &commit: commits)
        std::cout << commit << std::endl;
    return 0;
}
