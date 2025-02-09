#include "EchoCommand.hpp"

int EchoCommand::execute(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); i++) {
        if (args[i][0] == '$') {
            char* envValue = getenv(args[i].substr(1).c_str());
            if (envValue != nullptr) {
                std::cout << envValue << " ";
            }
        } else {
            std::cout << args[i] << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
