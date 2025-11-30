//            .\dsa-unified.bat
//to run the application on command line, paste above line in terminal

#include <iostream>
#include "core/repo.h"
#include "cli/parser.h"
#include "cli/commands.h"

int main(int argc, char* argv[]) {

    // Determine repository path (default to "./repo", or use --repo <path> flag)
    std::string repoPath = "./repo";

    // Parse --repo flag if present
    for (int i = 1; i < argc - 1; ++i) {
        if (std::string(argv[i]) == "--repo") {
            repoPath = argv[i + 1];
            // Remove --repo and its value from argv by shifting
            for (int j = i; j < argc - 2; ++j) {
                argv[j] = argv[j + 2];
            }
            argc -= 2;
            break;
        }
    }

    // Create Repo instance
    Repo repo(repoPath);

    // Parse command-line arguments
    Command cmd = parseCommandLine(argc, argv);

    if (cmd.name.empty()) {
        std::cout << "Usage:\n"
                    << "  --repo <path>         Set repository path (default: ./repo)\n"
                    << "\nCommands:\n"
                    << "  init                  Initialize repository\n"
                    << "  commit <file>         Commit a text file\n"
                    << "  log                   Show commit log\n"
                    << "  diff <v1> <v2>        Show diff between versions\n"
                    << "  checkout <versionID>  Restore a version\n"
                    << "  rollback <versionID> <output_file>  Rollback to version and save to file\n"
                    << "\nExamples:\n"
                    << "  init                           Initialize default repo (./repo)\n"
                    << "  --repo ./project1 init         Initialize custom repo\n"
                    << "  --repo ./project1 commit file  Commit to custom repo\n"
                    << "  rollback 2 restored.txt        Rollback to version 2 and save to restored.txt\n";
        return 0;
    }

    // Execute command
    CLI::executeCommand(repo, cmd);

    return 0;
}
