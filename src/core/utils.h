#pragma once
#include <string>
#include <vector>

namespace Utils {

    // File I/O
    bool writeFile(const std::string& path, const std::string& content);
    std::string readFile(const std::string& path);

    // Timestamp as string
    std::string currentTimestamp();

    // Simple string hash (placeholder for SHA-1 / SHA-256 later)
    std::string hashString(const std::string& input);

    // Join lines into a single string (with newline)
    std::string joinLines(const std::vector<std::string>& lines);

    // Split string into lines
    std::vector<std::string> splitLines(const std::string& text);
}