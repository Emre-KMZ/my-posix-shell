#include "EchoCommand.hpp"

int EchoCommand::execute(const std::vector<std::string>& args) {
    for (const auto& arg : args) {
        if (arg[0] == '$') {
            char* envValue = getenv(arg.substr(1).c_str());
            if (envValue != nullptr) {
                std::cout << envValue << " ";
            }
        } else {
            std::cout << arg << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
