//
// Created by leo on 05.08.24.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <filesystem>
#include <string>
#include <utility>
#include <vector>
#include <fkYAML/node.hpp>

#include "version.h"

struct ConventionConfig {
    using strVec = std::vector<std::string>;
private:
    strVec commitTypes;
    strVec commitScopes;
    std::map<VersionType, strVec> versionTypes;

public:
    explicit ConventionConfig(strVec cmTps, strVec cmSps): commitTypes(std::move(cmTps)), commitScopes(std::move(cmSps)) {};
    ConventionConfig() = default;
    strVec &getCommitTypes() {
        return commitTypes;
    }
    strVec &getCommitScopes() {
        return commitScopes;
    }

    strVec &getTypesForVersion(const VersionType vt) {
        return versionTypes[vt];
    }

    void addCommitTypeToVersion(const VersionType vt, const std::string &type) {
        versionTypes[vt].push_back(type);
    }
};

class Config {
public:
    Config();

    explicit Config(const std::filesystem::path& path);
    ConventionConfig* getConvention();
private:
    static fkyaml::node fromFile(const std::filesystem::path &path);
    ConventionConfig m_convention;
};



#endif //CONFIG_H
