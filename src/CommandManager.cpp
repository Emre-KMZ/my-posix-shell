#include <unistd.h>
#include <filesystem>
#include "CommandManager.hpp"
#include "commands/ExitCommand.hpp"
#include "commands/EchoCommand.hpp"
#include "commands/TypeCommand.hpp"
#include "commands/PwdCommand.hpp"
#include "commands/CdCommand.hpp"

namespace fs = std::filesystem;

std::string CommandManager::ProgramLookup(std::string command){
    std::istringstream ss(std::getenv("PATH"));
    
    if (fs::path(command).is_relative() && fs::exists(fs::current_path() / command)) {
        return fs::current_path() / command;
    }

    std::string pathStr;
    while (std::getline(ss, pathStr, ':')) {
        fs::path commandPath = (fs::path)pathStr / command; // append command to path

        if (fs::exists(commandPath)) {
            return commandPath;   
        }
    }
    return "";
}

CommandManager::CommandManager() {
    // Register commands
    commands["exit"] = std::make_unique<ExitCommand>();
    commands["echo"] = std::make_unique<EchoCommand>();
    commands["type"] = std::make_unique<TypeCommand>();
    commands["pwd"] = std::make_unique<PwdCommand>();
    commands["cd"] = std::make_unique<CdCommand>();
}

int CommandManager::executeCommand(const std::vector<std::string>& args) {
    std::string command = args[0];

    // built-ins
    auto it = commands.find(command);
    if (it != commands.end()) {
        return it->second->execute(args);
    }
    // path commands
    std::string commandPath = ProgramLookup(command);
    
    if (commandPath != "") {
        pid_t pid = fork();
        if (pid == 0) { // child
            char** argv = new char*[args.size() + 1];
            for (size_t i = 0; i < args.size(); i++) {
                argv[i] = const_cast<char*>(args[i].c_str());
            }
            argv[args.size()] = nullptr;
            execv(commandPath.c_str(), argv);
            delete[] argv;
            std::cerr << command << ": command not found" << std::endl;
            return -1;
        } else {
            int status;
            waitpid(pid, &status, 0);
            return WEXITSTATUS(status);
        }
    }

    std::cerr << command << ": command not found" << std::endl;
    return -1;
}

bool CommandManager::commandExists(const std::string& command) {
    return commands.find(command) != commands.end();
}