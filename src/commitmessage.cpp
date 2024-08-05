//
// Created by leo on 05.08.24.
//

#include "commitmessage.h"
#include "common.h"
#include <regex>



CommitMessage::CommitMessage(): type(), breaking(false) {
}

CommitMessage::CommitMessage(const std::vector<std::string> &parts) {
    if (parts.size() >= 5) {
        type = parts[0];
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

std::string CommitMessage::getCommitType() const {
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
