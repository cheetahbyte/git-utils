//
// Created by leo on 04.08.24.
//

#ifndef GITUTIL_H
#define GITUTIL_H
#include <string>
#include <vector>
#include "commit.h"


class GitUtil {
public:
    GitUtil() = default;

    static std::string getLog();

    static std::vector<Commit> getCommits() ;
private:
    static std::string exec(const char*);
};



#endif //GITUTIL_H
