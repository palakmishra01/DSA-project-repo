#pragma once
#include <string>
#include <vector>
#include "version.h"

class Repo {
private:
    std::string repoPath;                 // Path to repository directory
    std::vector<Version> versions;        // All committed versions
    std::string versionsFilePath;         // Path to versions.txt metadata file
    std::string currentText;              // Current working text

    void loadVersions();                  // Load versions from metadata file
    void saveVersions();                  // Save versions to metadata file

public:
    // Constructor: takes the repository path (e.g., "./repo")
    Repo(const std::string& path);

    // Initialize a new repository
    void init();

    // Commit the given text as a new version
    void commit(const std::string& text);

    // Display commit log (history)
    void log();

    // Show diff between two versions
    void diff(int versionA, int versionB);

    // Restore (checkout) a specific version
    void checkout(int versionID);

    // Get current repository path
    std::string getRepoPath() const;
};
