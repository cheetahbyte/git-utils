//
// Created by leo on 04.08.24.
//

#ifndef COMMIT_H
#define COMMIT_H
#include "commitmessage.h"
#include <string>

class Commit {
public:
    explicit Commit(std::string &rawCommit);
    Commit(std::string hash, std::string author, std::string date, std::string& message);
    friend std::ostream& operator<<(std::ostream& os, const Commit& commit);

    [[nodiscard]] CommitMessage getCommitMessage() const;
    [[nodiscard]] std::string getCommitType() const;
    [[nodiscard]] bool getIsBreaking() const;
private:
    std::string hash;
    std::string author;
    std::string date;
    CommitMessage message;
};

inline std::ostream& operator<<(std::ostream& os, const Commit& commit) {
    os << commit.hash;
    return os;
}



#endif //COMMIT_H
