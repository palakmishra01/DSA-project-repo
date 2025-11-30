#include "commands.h"
#include <iostream>
#include <fstream>

namespace CLI {

void executeCommand(Repo& repo, const Command& cmd) {
    if (cmd.name == "init") {
        repo.init();
    } 
    else if (cmd.name == "commit") {
        if (cmd.args.empty()) {
            std::cerr << "Usage: commit <file_path>\n";
            return;
        }
        // Read text from file
        std::string fileContent = "";
        std::ifstream ifs(cmd.args[0]);
        if (!ifs.is_open()) {
            std::cerr << "Failed to open file: " << cmd.args[0] << "\n";
            return;
        }
        fileContent.assign((std::istreambuf_iterator<char>(ifs)),
                           (std::istreambuf_iterator<char>()));
        ifs.close();

        repo.commit(fileContent);
    } 
    else if (cmd.name == "log") {
        repo.log();
    } 
    else if (cmd.name == "diff") {
        if (cmd.args.size() < 2) {
            std::cerr << "Usage: diff <versionA> <versionB>\n";
            return;
        }
        int a = std::stoi(cmd.args[0]);
        int b = std::stoi(cmd.args[1]);
        repo.diff(a, b);
    } 
    else if (cmd.name == "checkout") {
        if (cmd.args.empty()) {
            std::cerr << "Usage: checkout <versionID>\n";
            return;
        }
        int versionID = std::stoi(cmd.args[0]);
        repo.checkout(versionID);
    }
    else if (cmd.name == "rollback") {
        if (cmd.args.size() < 2) {
            std::cerr << "Usage: rollback <versionID> <output_file_path>\n";
            return;
        }
        int versionID = std::stoi(cmd.args[0]);
        std::string outputFilePath = cmd.args[1];
        repo.rollback(versionID, outputFilePath);
    }
    else {
        std::cerr << "Unknown command: " << cmd.name << "\n";
    }
}

}
