#include "diff.h"
#include "utils.h"

#include <vector>
#include <string>
#include <algorithm>

namespace Diff {

std::vector<std::string> generate(const std::string& oldText, const std::string& newText) {
    std::vector<std::string> oldLines = Utils::splitLines(oldText);
    std::vector<std::string> newLines = Utils::splitLines(newText);
    std::vector<std::string> diff;

    size_t oldSize = oldLines.size();
    size_t newSize = newLines.size();
    size_t i = 0, j = 0;

    while (i < oldSize || j < newSize) {
        if (i < oldSize && j < newSize) {
            if (oldLines[i] == newLines[j]) {
                // same line, skip
                ++i; ++j;
            } else {
                // line changed: mark deletion and addition
                diff.push_back("- " + oldLines[i]);
                diff.push_back("+ " + newLines[j]);
                ++i; ++j;
            }
        } else if (i < oldSize) {
            // leftover deletions
            diff.push_back("- " + oldLines[i]);
            ++i;
        } else if (j < newSize) {
            // leftover additions
            diff.push_back("+ " + newLines[j]);
            ++j;
        }
    }

    return diff;
}

} // namespace Diff