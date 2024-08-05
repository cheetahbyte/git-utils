//
// Created by leo on 05.08.24.
//

#include "config.h"
#include <fkYAML/node.hpp>
#include <fstream>
#include <iostream>

std::vector<std::string> yamlListToVector(const fkyaml::node &node) {
    std::vector<std::string> result;
    std::cout << node << std::endl;
    std::cout << node.is_sequence() << std::endl;
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
    m_convention = ConventionConfig(yamlListToVector(conventioNode["commitTypes"]), yamlListToVector(conventioNode["commitScopes"]));
}

Config::Config(const std::filesystem::path &path) {
    const auto &rootNode = fromFile(path);
    const auto conventioNode = rootNode["convention"];
    m_convention = ConventionConfig(yamlListToVector(conventioNode["commitTypes"]), yamlListToVector(conventioNode["commitScopes"]));
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
