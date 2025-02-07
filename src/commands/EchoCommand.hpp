#pragma once
#include "../Command.hpp"

class EchoCommand : public Command {
    int execute (const std::vector<std::string>& args) override;
};