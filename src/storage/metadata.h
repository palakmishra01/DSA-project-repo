#pragma once
#include "../core/version.h"
#include <vector>
#include <string>

namespace Metadata {

    // Save vector of Version metadata to disk (Phase 1: optional JSON)
    void saveMetadata(const std::string& path, const std::vector<Version>& versions);

    // Load vector of Version metadata from disk
    std::vector<Version> loadMetadata(const std::string& path);

}