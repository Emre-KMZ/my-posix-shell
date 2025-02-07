#pragma once
#include "../Command.hpp"

class ExitCommand : public Command {
    int execute (const std::vector<std::string>& args) override;
};