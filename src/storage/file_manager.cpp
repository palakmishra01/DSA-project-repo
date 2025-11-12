#include "file_manager.h"
#include "../core/crypto.h"
#include <fstream>

namespace FileManager {

bool saveText(const std::string& path, const std::string& content) {
    // For Phase 1: no encryption
    std::ofstream ofs(path, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) return false;

    std::string data = Crypto::encrypt(content, "phase1key"); // stub
    ofs << data;
    ofs.close();
    return true;
}

std::string loadText(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) return "";

    std::string data((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
    ifs.close();

    return Crypto::decrypt(data, "phase1key"); // stub
}

}