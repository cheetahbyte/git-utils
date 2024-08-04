//
// Created by leo on 04.08.24.
//

#ifndef COMMIT_H
#define COMMIT_H
#include <string>

class Commit {
public:
    explicit Commit(const std::string &rawCommit);
    Commit(std::string hash, std::string author, std::string date, std::string message);
    friend std::ostream& operator<<(std::ostream& os, const Commit& commit);

private:
    std::string hash;
    std::string author;
    std::string date;
    std::string message;
};

inline std::ostream& operator<<(std::ostream& os, const Commit& commit) {
    os << commit.hash;
    return os;
}



#endif //COMMIT_H
