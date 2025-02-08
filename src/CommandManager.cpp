#include <unistd.h>
#include <filesystem>
#include "CommandManager.hpp"
#include "commands/ExitCommand.hpp"
#include "commands/EchoCommand.hpp"
#include "commands/TypeCommand.hpp"

std::string CommandManager::ProgramLookup(std::string command){
    std::istringstream ss(std::getenv("PATH"));
    std::string path;
    while (std::getline(ss, path, ':')) {
        // const char* commandPath = strcat((strcat((char*)path.c_str(), (char*)"/")), (char*)command.c_str());
        std::string commandPath = path + "/" + command;

        if (std::filesystem::exists(commandPath)) {
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
}

int CommandManager::executeCommand(const std::string& command, const std::vector<std::string>& args) {
    // built-ins
    auto it = commands.find(command);
    if (it != commands.end()) {
        return it->second->execute(args);
    }
    // path commands
    std::string commandPath = ProgramLookup(command);
    
    if (commandPath != "") {
        pid_t pid = fork();
        if (pid == 0) {
            char* argv[args.size() + 2];
            argv[0] = (char*)commandPath.c_str();
            for (size_t i = 0; i < args.size(); i++) {
                argv[i + 1] = (char*)args[i].c_str();
            }
            argv[args.size() + 1] = NULL;
            execv(commandPath.c_str(), argv);
            std::cerr << command << ": command not found" << std::endl;
            return -1;
        }
        waitpid(pid, NULL, 0);
        return 0;
    }

    std::cerr << command << ": command not found" << std::endl;
    return -1;
}

bool CommandManager::commandExists(const std::string& command) {
    return commands.find(command) != commands.end();
}