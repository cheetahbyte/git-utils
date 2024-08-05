//
// Created by leo on 05.08.24.
//

#ifndef VERSION_H
#define VERSION_H
#include <sstream>
#include <string>
#include <utility>


class Version {
public:
    Version(const int maj, const int min, const int pat, std::string flg): major(maj), minor(min), patch(pat),
                                                                           flag(std::move(flg)) {
    };

    Version(): major(0), minor(0), patch(0) {};
    void increaseMajor() {
        major++;
    }
    void increaseMinor() {
        minor++;
    }
    void increasePatch() {
        patch++;
    }

    [[nodiscard]] std::string buildString() const {
        std::ostringstream oss;
        oss << major << "." << minor << "." << patch;
        if (!flag.empty()) {
            oss << "-" << flag;
        }
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Version& v);
private:
    unsigned int major;
    unsigned int minor;
    unsigned int patch;
    std::string flag;
};


inline std::ostream& operator<<(std::ostream& os, const Version& v) {
    os << v.buildString();
    return os;
}

#endif //VERSION_H
