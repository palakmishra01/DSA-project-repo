#include "utils.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/types.h>
#endif

namespace Utils {

bool writeFile(const std::string& path, const std::string& content) {
    std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) return false;
    ofs << content;
    ofs.close();
    return true;
}

std::string readFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return "";

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

std::string currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&t_c), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string hashString(const std::string& input) {
    // Simple placeholder hash: sum of ASCII modulo 1e9
    unsigned long long hash = 0;
    for (char c : input) {
        hash = (hash * 31 + static_cast<unsigned long long>(c)) % 1000000000;
    }
    return std::to_string(hash);
}

std::string joinLines(const std::vector<std::string>& lines) {
    std::string result;
    for (const auto& line : lines) {
        result += line + "\n";
    }
    return result;
}

std::vector<std::string> splitLines(const std::string& text) {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

bool directoryExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

bool createDirectory(const std::string& path) {
    return mkdir(path.c_str(), 0755) == 0 || directoryExists(path);
}

} // namespace Utils