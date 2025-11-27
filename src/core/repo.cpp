#include "repo.h"
#include "diff.h"
#include "utils.h"
#include "../storage/metadata.h"
#include <iostream>
#include <fstream>

Repo::Repo(const std::string& path)
    : repoPath(path), versionsFilePath(path + "/versions.txt"), currentText("") {
}

void Repo::init() {
    // Create repository directory if it doesn't exist
    if (!Utils::directoryExists(repoPath)) {
        Utils::createDirectory(repoPath);
        std::cout << "Repository initialized at: " << repoPath << "\n";
    } else {
        std::cout << "Repository already exists at: " << repoPath << "\n";
    }

    // Create versions.txt if it doesn't exist
    if (!Utils::fileExists(versionsFilePath)) {
        std::ofstream ofs(versionsFilePath);
        ofs.close();
        std::cout << "Created versions metadata file.\n";
    }

    // Load existing versions
    loadVersions();
}

void Repo::commit(const std::string& text) {
    // Check if repo is initialized
    if (!Utils::directoryExists(repoPath)) {
        std::cerr << "Error: Repository not initialized. Run 'init' first.\n";
        return;
    }

    // Load existing versions
    loadVersions();

    // Create new version
    Version newVersion;
    newVersion.id = versions.size();
    newVersion.timestamp = Utils::currentTimestamp();
    newVersion.hash = Utils::hashString(text);

    // Generate diff against previous version
    std::string diffText;
    if (versions.empty()) {
        // First commit: entire text is a diff
        auto lines = Utils::splitLines(text);
        for (const auto& line : lines) {
            diffText += "+ " + line + "\n";
        }
    } else {
        // Generate diff from previous version
        auto diffLines = Diff::generate(currentText, text);
        diffText = Utils::joinLines(diffLines);
    }

    // Save diff to file
    std::string diffFilename = "diff_" + std::to_string(newVersion.id) + ".txt";
    newVersion.diffPath = repoPath + "/" + diffFilename;
    Utils::writeFile(newVersion.diffPath, diffText);

    // Update current text
    currentText = text;

    // Add version to list and save
    versions.push_back(newVersion);
    saveVersions();

    std::cout << "Committed version " << newVersion.id
              << " (hash: " << newVersion.hash.substr(0, 8) << "...)\n";
}

void Repo::log() {
    if (!Utils::directoryExists(repoPath)) {
        std::cerr << "Error: Repository not initialized.\n";
        return;
    }

    loadVersions();

    if (versions.empty()) {
        std::cout << "No commits yet.\n";
        return;
    }

    std::cout << "Commit History:\n";
    std::cout << "----------------------------------------\n";
    for (const auto& v : versions) {
        std::cout << "Version " << v.id << "\n";
        std::cout << "  Timestamp: " << v.timestamp << "\n";
        std::cout << "  Hash: " << v.hash.substr(0, 16) << "...\n";
        std::cout << "  Diff: " << v.diffPath << "\n";
        std::cout << "----------------------------------------\n";
    }
}

void Repo::diff(int versionA, int versionB) {
    if (!Utils::directoryExists(repoPath)) {
        std::cerr << "Error: Repository not initialized.\n";
        return;
    }

    loadVersions();

    if (versionA < 0 || versionA >= (int)versions.size() ||
        versionB < 0 || versionB >= (int)versions.size()) {
        std::cerr << "Error: Invalid version numbers.\n";
        return;
    }

    // Read diff files for both versions
    std::string diffA = Utils::readFile(versions[versionA].diffPath);
    std::string diffB = Utils::readFile(versions[versionB].diffPath);

    std::cout << "Diff between version " << versionA << " and version " << versionB << ":\n";
    std::cout << "========================================\n";
    std::cout << "Version " << versionA << " diff:\n";
    std::cout << diffA << "\n";
    std::cout << "========================================\n";
    std::cout << "Version " << versionB << " diff:\n";
    std::cout << diffB << "\n";
    std::cout << "========================================\n";
}

void Repo::checkout(int versionID) {
    if (!Utils::directoryExists(repoPath)) {
        std::cerr << "Error: Repository not initialized.\n";
        return;
    }

    loadVersions();

    if (versionID < 0 || versionID >= (int)versions.size()) {
        std::cerr << "Error: Invalid version ID.\n";
        return;
    }

    // Read the diff file
    std::string diffContent = Utils::readFile(versions[versionID].diffPath);

    std::cout << "Checked out version " << versionID << ":\n";
    std::cout << "========================================\n";
    std::cout << diffContent << "\n";
    std::cout << "========================================\n";
    std::cout << "Hash: " << versions[versionID].hash << "\n";
    std::cout << "Timestamp: " << versions[versionID].timestamp << "\n";
}

std::string Repo::getRepoPath() const {
    return repoPath;
}

void Repo::loadVersions() {
    if (Utils::fileExists(versionsFilePath)) {
        versions = Metadata::loadMetadata(versionsFilePath);
    }
}

void Repo::saveVersions() {
    Metadata::saveMetadata(versionsFilePath, versions);
}
