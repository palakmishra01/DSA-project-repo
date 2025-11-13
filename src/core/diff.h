#pragma once
#include <string>
#include <vector>

namespace Diff {

    // Generate a diff between oldText and newText
    // Returns lines prefixed with "+" (addition) or "-" (deletion)
    std::vector<std::string> generate(const std::string& oldText, const std::string& newText);

}