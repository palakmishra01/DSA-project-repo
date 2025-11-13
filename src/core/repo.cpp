#include "repo.h"
#include "version.h"
#include "diff.h"
#include "patch.h"
#include "utils.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

Repo::Repo(const std::string& path) : repoPath(path) {
    loadVersions();
}

void Repo::init() {
    if (!fs::exists(repoPath)) {
        fs::create_directories(repoPath);
        std::cout << "Initialized empty repository at: " << repoPath << "\n";
    } else {
        std::cout << "Repository already exists at: " << repoPath << "\n";
    }

    // Initialize first version if none exists
    if (versions.empty()) {
        Version baseVersion;
        baseVersion.id = 0;
        baseVersion.timestamp = Utils::currentTimestamp();
        baseVersion.diffPath = ""; // empty diff for base
        baseVersion.hash = Utils::hashString(""); // empty content
        versions.push_back(baseVersion);
        saveVersions();
    }
}

void Repo::commit(const std::string& text) {
    std::string latestText = getLatestText();

    // Compute diff between latest version and new text
    std::vector<std::string> diffLines = Diff::generate(latestText, text);

    // Prepare new version
    Version newVersion;
    newVersion.id = versions.empty() ? 0 : versions.back().id + 1;
    newVersion.timestamp = Utils::currentTimestamp();

    // Save diff to disk
    std::string diffFile = repoPath + "/diff_" + std::to_string(newVersion.id) + ".txt";
    // Ensure repo directory exists before writing
    if (!fs::exists(repoPath)) fs::create_directories(repoPath);
    bool wrote = Utils::writeFile(diffFile, Utils::joinLines(diffLines));
    if (!wrote) {
        std::cerr << "Failed to write diff file: " << diffFile << "\n";
        return;
    }
    newVersion.diffPath = diffFile;

    // Compute hash of new text
    newVersion.hash = Utils::hashString(text);

    // Add to versions and save metadata
    versions.push_back(newVersion);
    saveVersions();

    std::cout << "Committed version " << newVersion.id << " with " << diffLines.size() << " diff lines.\n";
}

void Repo::log() const {
    if (versions.empty()) {
        std::cout << "No versions found.\n";
        return;
    }

    std::cout << "Version log:\n";
    for (const auto& v : versions) {
        std::cout << "------------------------------------------------------------\n";
        std::cout << "Version " << v.id << ":\n";
        std::cout << "  Timestamp : " << v.timestamp << "\n";
        std::cout << "  Hash      : " << v.hash << "\n";
        std::cout << "  Diff file : " << (v.diffPath.empty() ? "<none>" : v.diffPath) << "\n";

        // Provide a short preview of the version's content to make the log easier to scan
        std::string textPreview;
        if (v.id == 0) {
            textPreview = "<empty base version>";
        } else {
            std::string full = Patch::reconstructVersion(*this, v);
            if (full.empty()) textPreview = "<empty>";
            else {
                auto pos = full.find('\n');
                textPreview = (pos == std::string::npos) ? full : full.substr(0, pos);
                if (textPreview.size() > 120) textPreview = textPreview.substr(0, 120) + "...";
            }
        }
        std::cout << "  Preview   : " << textPreview << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
}

void Repo::diff(int versionA, int versionB) const {
    const Version* vA = findVersion(versionA);
    const Version* vB = findVersion(versionB);

    if (!vA || !vB) {
        std::cerr << "One of the version IDs does not exist.\n";
        return;
    }

    std::string textA = (vA->id == 0) ? "" : Patch::reconstructVersion(*this, *vA);
    std::string textB = (vB->id == 0) ? "" : Patch::reconstructVersion(*this, *vB);

    std::vector<std::string> diffLines = Diff::generate(textA, textB);

    std::cout << "Diff between versions " << versionA << " and " << versionB << ":\n";
    for (const auto& line : diffLines)
        std::cout << line << "\n";
}

void Repo::checkout(int versionID) {
    const Version* v = findVersion(versionID);
    if (!v) {
        std::cerr << "Version ID " << versionID << " does not exist.\n";
        return;
    }

    std::string text = (v->id == 0) ? "" : Patch::reconstructVersion(*this, *v);

    // Overwrite latest working file (or provide UI later)
    std::string outFile = repoPath + "/current_version.txt";
    Utils::writeFile(outFile, text);
    std::cout << "Checked out version " << versionID << " to " << outFile << "\n";
}

std::string Repo::getLatestText() const {
    if (versions.empty()) return "";

    const Version& latest = versions.back();
    return (latest.id == 0) ? "" : Patch::reconstructVersion(*this, latest);
}

// -----------------------
// Private helpers
// -----------------------
void Repo::loadVersions() {
    versions.clear();
    std::string metaFile = repoPath + "/versions.txt";
    if (!fs::exists(metaFile)) return;

    std::ifstream in(metaFile);
    if (!in.is_open()) return;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Version v;
        std::string idStr;
        // Format: id\ttimestamp\thash\tdiffPath
        if (!std::getline(iss, idStr, '\t')) continue;
        try {
            v.id = std::stoi(idStr);
        } catch (...) { continue; }
        std::getline(iss, v.timestamp, '\t');
        std::getline(iss, v.hash, '\t');
        std::getline(iss, v.diffPath, '\t');
        versions.push_back(v);
    }
}

void Repo::saveVersions() const {
    if (!fs::exists(repoPath)) fs::create_directories(repoPath);
    std::string metaFile = repoPath + "/versions.txt";
    std::ofstream out(metaFile, std::ios::trunc);
    if (!out.is_open()) return;
    // Write each version as: id\ttimestamp\thash\tdiffPath\n
    for (const auto& v : versions) {
        out << v.id << '\t' << v.timestamp << '\t' << v.hash << '\t' << v.diffPath << '\n';
    }
}

const Version* Repo::findVersion(int versionID) const {
    for (const auto& v : versions) {
        if (v.id == versionID) return &v;
    }
    return nullptr;
}

const Version* Repo::getVersion(int versionID) const {
    return findVersion(versionID);
}
