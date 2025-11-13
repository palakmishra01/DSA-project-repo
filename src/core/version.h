#pragma once
#include <string>

struct Version {
    int id;                 // version number
    std::string timestamp;  // commit timestamp
    std::string diffPath;   // path to diff file
    std::string hash;       // hash of version text
};