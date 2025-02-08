#pragma once
#include "../Command.hpp"
#include <filesystem>

class PwdCommand : public Command {
    int execute (const std::vector<std::string>& args) override;
};