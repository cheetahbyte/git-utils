//
// Created by leo on 05.08.24.
//

#ifndef COMMITMESSAGE_H
#define COMMITMESSAGE_H
#include <string>
#include <vector>

enum class CommitType {
    FEATURE,
    FIXTURE,
    REFACTOR,
    STYLE,
    DOCS,
    BUILD,
    TEST,
    PERFORMANCE,
    CHORE,
    REVERT,
    DEPENDENCIES
};

class CommitMessage {
public:
    CommitMessage();

    explicit CommitMessage(const std::vector<std::string> &);

    [[nodiscard]] std::string getTitle() const;

    [[nodiscard]] std::string getDescription() const;

    [[nodiscard]] CommitType getCommitType() const;

    [[nodiscard]] bool getIsBreaking() const;

    static std::vector<std::string> parseCommitMessage(std::string &);

private:
    CommitType type;

    std::string title;

    std::string scope;

    std::string footer;

    std::string description;

    bool breaking;
};


#endif //COMMITMESSAGE_H
