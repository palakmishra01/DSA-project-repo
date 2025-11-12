#include "metadata.h"
#include "../core/utils.h"
#include <iostream>

namespace Metadata {

void saveMetadata(const std::string& path, const std::vector<Version>& versions) {
    // Phase 1: simple plain-text format: id|timestamp|diffPath|hash
    std::string content;
    for (const auto& v : versions) {
        content += std::to_string(v.id) + "|" + v.timestamp + "|" + v.diffPath + "|" + v.hash + "\n";
    }
    if (!Utils::writeFile(path, content)) {
        std::cerr << "Failed to save metadata to: " << path << "\n";
    }
}

std::vector<Version> loadMetadata(const std::string& path) {
    std::vector<Version> versions;
    std::string content = Utils::readFile(path);
    if (content.empty()) return versions;

    std::vector<std::string> lines = Utils::splitLines(content);
    for (const auto& line : lines) {
        if (line.empty()) continue;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos)
            continue;

        Version v;
        v.id = std::stoi(line.substr(0, pos1));
        v.timestamp = line.substr(pos1 + 1, pos2 - pos1 - 1);
        v.diffPath = line.substr(pos2 + 1, pos3 - pos2 - 1);
        v.hash = line.substr(pos3 + 1);
        versions.push_back(v);
    }

    return versions;
}

}