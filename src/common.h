//
// Created by leo on 04.08.24.
//

#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>

inline std::vector<std::string> splitByDelimiter(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));

    return result;
}


// Function to remove all newline characters from a string
inline std::string removeNewlines(const std::string& str) {
    std::string result = str;
    std::erase(result, '\n');
    return result;
}
#endif //COMMON_H
