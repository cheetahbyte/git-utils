//
// Created by leo on 05.08.24.
//

#include "config.h"
#include <fkYAML/node.hpp>
#include <fstream>
#include <iostream>

std::vector<std::string> yamlListToVector(const fkyaml::node &node) {
    std::vector<std::string> result;
    if (node.is_sequence()) {
        for (const auto &i: node) {
            if (const auto val = i.get_value<std::string>(); val.empty())
                result.push_back(val);
        }
    }
    return result;
}

Config::Config() {
    const auto &rootNode = fromFile("releases.yaml");
    const auto conventioNode = rootNode["convention"];
    m_convention = ConventionConfig(yamlListToVector(conventioNode["commitTypes"]),
                                    yamlListToVector(conventioNode["commitScopes"]));
    // TODO: somehow, yamlListTovector didnt work here
    for (const auto& x: conventioNode["versions"]["minor"]) {
        m_convention.addCommitTypeToVersion(VersionType::MINOR, x.get_value<std::string>());
    }
    for (const auto& x: conventioNode["versions"]["patch"]) {
        m_convention.addCommitTypeToVersion(VersionType::PATCH, x.get_value<std::string>());
    }
}


Config::Config(const std::filesystem::path &path) {
    const auto &rootNode = fromFile(path);
    const auto conventioNode = rootNode["convention"];
    m_convention = ConventionConfig(yamlListToVector(conventioNode["commitTypes"]),
                                    yamlListToVector(conventioNode["commitScopes"]));
    // TODO: somehow, yamlListTovector didnt work here
    for (const auto& x: conventioNode["versions"]["minor"]) {
        m_convention.addCommitTypeToVersion(VersionType::MINOR, x.get_value<std::string>());
    }
    for (const auto& x: conventioNode["versions"]["patch"]) {
        m_convention.addCommitTypeToVersion(VersionType::PATCH, x.get_value<std::string>());
    }
}

ConventionConfig *Config::getConvention() {
    return &m_convention;
}

fkyaml::node Config::fromFile(const std::filesystem::path &path) {
    std::ifstream ifs(path);
    if(!ifs.is_open()) {
        throw std::runtime_error("config file cannot be opened");
    }
    fkyaml::node root = fkyaml::node::deserialize(ifs);
    return root;
}
