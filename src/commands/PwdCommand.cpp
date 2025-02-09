#include "PwdCommand.hpp"


int PwdCommand::execute(const std::vector<std::string>& args) {
    std::cout << std::string(std::filesystem::current_path()) << std::endl;
    return 0;
}
