#pragma once
#include <string>
#include <vector>
#include "repo.h"

namespace Patch {

    // Reconstruct the full text of a given version
    std::string reconstructVersion(const Repo& repo, const Version& version);

}