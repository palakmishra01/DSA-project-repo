#include "../src/core/repo.h"
#include "../src/core/utils.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void testRepo() {
    std::string repoPath = "./test_repo";
    if (fs::exists(repoPath)) fs::remove_all(repoPath);

    Repo repo(repoPath);
    repo.init();

    // Create a file to commit
    std::string file1 = repoPath + "/file1.txt";
    std::ofstream(file1) << "hello\nworld";

    repo.commit("hello\nworld");
    repo.commit("hello\nworld!\nnew line");

    auto latestText = repo.getLatestText();
    assert(latestText.find("new line") != std::string::npos);

    repo.log();

    repo.checkout(1);
    std::string currentVersion = Utils::readFile(repoPath + "/current_version.txt");
    assert(currentVersion.find("world") != std::string::npos);

    std::cout << "testRepo passed.\n";
}

int main() {
    testRepo();
    return 0;
}
