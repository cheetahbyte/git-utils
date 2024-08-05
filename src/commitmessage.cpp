//
// Created by leo on 05.08.24.
//

#include "commitmessage.h"
#include "common.h"
#include <iostream>
#include <utility>
#include <map>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>

const std::map<CommitType, std::string> commitTypeToString = {
    {CommitType::FEATURE, "feat"},
    {CommitType::FIXTURE, "fix"},
    {CommitType::REFACTOR, "refactor"},
    {CommitType::STYLE, "style"},
    {CommitType::DOCS, "docs"},
    {CommitType::BUILD, "build"},
    {CommitType::TEST, "test"},
    {CommitType::PERFORMANCE, "perf"},
    {CommitType::CHORE, "chore"},
    {CommitType::REVERT, "revert"},
    {CommitType::DEPENDENCIES, "deps"}
};

std::map<std::string, CommitType> createReverseMap(const std::map<CommitType, std::string> &originalMap) {
    std::map<std::string, CommitType> reversedMap;
    for (const auto &[fst, snd]: originalMap) {
        reversedMap[snd] = fst;
    }
    return reversedMap;
}

std::string toString(const CommitType type) {
    if (const auto it = commitTypeToString.find(type); it != commitTypeToString.end()) {
        return it->second;
    }
    return "Unknown";
}

CommitType toCommitType(const std::string &typeStr) {
    static const auto stringToCommitType = createReverseMap(commitTypeToString);
    if (const auto it = stringToCommitType.find(typeStr); it != stringToCommitType.end()) {
        return it->second;
    }
    return CommitType::FEATURE;
}


CommitMessage::CommitMessage(): type(), breaking(false) {
}

CommitMessage::CommitMessage(const std::vector<std::string> &parts) {
    if (parts.size() >= 5) {
        type = toCommitType(parts[0]);
        scope = removeNewlines(parts[1]);
        title = removeNewlines(parts[2]);
        description = removeNewlines(parts[3]);
        footer = removeNewlines(parts[4]);
        breaking = footer.find("BREAKING CHANGE") != std::string::npos;
    }
}

std::string CommitMessage::getTitle() const {
    return title;
}

std::string CommitMessage::getDescription() const {
    return description;
}

CommitType CommitMessage::getCommitType() const {
    return type;
}

bool CommitMessage::getIsBreaking() const {
    return breaking;
}

std::vector<std::string> CommitMessage::parseCommitMessage(std::string& message) {
    std::vector<std::string> result(5);
    const std::regex regexPattern(R"((\w+)(?:\(([\w\-]+)\))?:\s*(.+?)(?:\n\n(.*?))?(?:\n\n(.*))?$)");
    const auto trimmedMessage = removeNewlines(message);
    if (std::smatch matches; std::regex_match(trimmedMessage, matches, regexPattern)) {
        result[0] = matches[1].str(); // Type
        result[1] = matches[2].str(); // Scope
        result[2] = matches[3].str(); // Title
        result[3] = matches[4].str(); // Description
        result[4] = matches[5].str(); // Footer
    }
    return result;
}
