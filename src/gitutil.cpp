//
// Created by leo on 04.08.24.
//
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <regex>
#include "gitutil.h"


std::vector<std::string> splitGitLog(const std::string& gitLog) {
    std::vector<std::string> commits;
    std::regex commitRegex(R"(commit\s[0-9a-f]{40})");
    auto commitBegin = std::sregex_iterator(gitLog.begin(), gitLog.end(), commitRegex);
    auto commitEnd = std::sregex_iterator();

    if (commitBegin == commitEnd) {
        // No commits found
        return commits;
    }

    auto nextCommit = commitBegin;
    ++nextCommit;

    for (auto it = commitBegin; it != commitEnd; ++it) {
        auto start = it->position();
        auto end = (nextCommit != commitEnd) ? nextCommit->position() : gitLog.length();
        commits.push_back(gitLog.substr(start, end - start));
        if (nextCommit != commitEnd) {
            ++nextCommit;
        }
    }

    return commits;
}

std::string GitUtil::getLog() {
    const std::string log = exec("git log");
    return log;
}

std::vector<Commit> GitUtil::getCommits() {
    std::vector<Commit> commits;
    for (const auto log =  getLog(); auto commit: splitGitLog(log))
        commits.emplace_back(commit);
    std::reverse(commits.begin(), commits.end());
    return commits;
}

Version GitUtil::calculateVersion() {
    Version version;
    for (const auto& commits = getCommits(); const auto &commit: commits) {
        switch(commit.getCommitType()) {
            case CommitType::FEATURE:
                version.increaseMinor();
                break;
            case CommitType::FIXTURE:case CommitType::REFACTOR: case CommitType::CHORE:
                version.increasePatch();
            break;
            default:
                break;
        }
        if (commit.getIsBreaking())
            version.increaseMajor();
    }
    return version;
}

Version GitUtil::getVersion() {
    return calculateVersion();
}

std::string GitUtil::exec(const char *cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    const std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
