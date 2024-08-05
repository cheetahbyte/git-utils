//
// Created by leo on 04.08.24.
//

#ifndef COMMON_H
#define COMMON_H
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>


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

// Trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// Trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// Function to remove all newline characters from a string
inline std::string removeNewlines(const std::string& str) {
    std::string result = str;
    std::erase(result, '\n');
    trim(result);
    return result;
}

template <typename T>
bool contains(const std::vector<T> &vec, const T element) {
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}


#endif //COMMON_H
