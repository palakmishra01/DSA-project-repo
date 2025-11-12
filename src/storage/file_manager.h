#pragma once
#include <string>

namespace FileManager {

    // Save text to disk (optionally encrypt)
    bool saveText(const std::string& path, const std::string& content);

    // Load text from disk (optionally decrypt)
    std::string loadText(const std::string& path);

}