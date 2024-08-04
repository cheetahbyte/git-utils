//
// Created by leo on 04.08.24.
//
#include "commit.h"
#include <sstream>
#include <utility>
#include "common.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, last - first + 1);
}

std::array<std::string, 4> splitCommit(const std::string& commit) {
    std::istringstream stream(commit);
    std::string line;
    std::array<std::string, 4> parts; // Array to store commit hash, author, date, and message

    // Extract the first line for commit hash
    std::getline(stream, line);
    parts[0] = trim(line.substr(7)); // Remove "commit " from the beginning

    // Extract the second line for author
    std::getline(stream, line);
    parts[1] = trim(line.substr(7)); // Remove "Author: " from the beginning

    // Extract the third line for date
    std::getline(stream, line);
    parts[2] = trim(line.substr(6)); // Remove "Date: " from the beginning

    // Read the rest of the lines for the commit message
    std::string message;
    while (std::getline(stream, line)) {
        message += line + "\n";
    }
    parts[3] = message;

    return parts;
}

Commit::Commit(const std::string &rawCommit) {
    const auto &[hash, author, date, message] = splitCommit(rawCommit);
    this->hash = hash;
    this->author = author;
    this->date = date;
    this->message = message;
}

Commit::Commit(std::string hash, std::string author, std::string date, std::string message): hash(std::move(hash)),
    author(std::move(author)), date(std::move(date)), message(std::move(message)) {
}
