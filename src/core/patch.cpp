#include "patch.h"
#include "utils.h"
#include "diff.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace Patch {

// Helper to apply a single diff file to text
static std::string applyDiffFile(const std::string& baseText, const std::string& diffPath) {
    std::vector<std::string> lines = Utils::splitLines(baseText);
    std::vector<std::string> diffLines = Utils::splitLines(Utils::readFile(diffPath));
    std::vector<std::string> result;

    size_t i = 0; // index in original lines
    for (const auto& dline : diffLines) {
        if (dline.empty()) continue;

        if (dline[0] == '-') {
            std::string lineToRemove = dline.substr(2);
            // skip lines in original that match lineToRemove
            if (i < lines.size() && lines[i] == lineToRemove) {
                ++i; // remove this line
            } else {
                // mismatch: skip
                ++i;
            }
        } else if (dline[0] == '+') {
            result.push_back(dline.substr(2)); // add line
        } else {
            // unknown format, ignore
        }
    }

    // Append remaining original lines not removed
    while (i < lines.size()) {
        result.push_back(lines[i]);
        ++i;
    }

    return Utils::joinLines(result);
}

// Reconstruct a version by applying diffs from base
std::string reconstructVersion(const Repo& repo, const Version& version) {
    // Simplified implementation - read the diff file directly
    // In a full implementation, this would apply all diffs sequentially
    if (!version.diffPath.empty() && Utils::fileExists(version.diffPath)) {
        return Utils::readFile(version.diffPath);
    }
    return "";
}

} // namespace Patch