#include "EchoCommand.hpp"

int EchoCommand::execute(const std::vector<std::string>& args) {
    for (const auto& arg : args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;
    return 0;
}
