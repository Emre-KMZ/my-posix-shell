#pragma once
#include "../Command.hpp"

class TypeCommand : public Command {
    int execute (const std::vector<std::string>& args) override;
};