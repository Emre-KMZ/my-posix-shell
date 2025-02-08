#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "Command.hpp"

class CommandManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;

public:
    CommandManager();
    int executeCommand(const std::string& command, const std::vector<std::string>& args);
    bool commandExists(const std::string& command);
    std::string ProgramLookup(std::string command);
};
