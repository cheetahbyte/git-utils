//
// Created by leo on 04.08.24.
//
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <regex>
#include "common.h"
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
    for (const auto log =  getLog(); const auto& commit: splitGitLog(log))
        commits.emplace_back(commit);
    return commits;
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
