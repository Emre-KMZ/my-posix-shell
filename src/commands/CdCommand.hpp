#pragma once
#include "../Command.hpp"
#include <filesystem>


class CdCommand : public Command {
    int execute (const std::vector<std::string>& args) override;
};