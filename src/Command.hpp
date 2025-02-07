#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

// base class for commands
class Command {
public:
    virtual ~Command() = default;
    virtual int execute(const std::vector<std::string>& args) = 0;
};
