#include "CommandManager.hpp"
#include "commands/ExitCommand.hpp"
#include "commands/EchoCommand.hpp"
#include "commands/TypeCommand.hpp"

CommandManager::CommandManager() {
    // Register commands
    commands["exit"] = std::make_unique<ExitCommand>();
    commands["echo"] = std::make_unique<EchoCommand>();
    commands["type"] = std::make_unique<TypeCommand>();
}

int CommandManager::executeCommand(const std::string& command, const std::vector<std::string>& args) {
    auto it = commands.find(command);
    if (it != commands.end()) {
        return it->second->execute(args);
    }
    std::cerr << command << ": command not found" << std::endl;
    return -1;
}

bool CommandManager::commandExists(const std::string& command) {
    return commands.find(command) != commands.end();
}