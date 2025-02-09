#include "CdCommand.hpp"

namespace fs = std::filesystem;

int CdCommand::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        try {
            fs::current_path(fs::path(getenv("HOME")));
        } catch (fs::filesystem_error& e) {
            std::cerr << "cd: " << e.what() << std::endl;
            return -1;
        }
    } else {
        fs::path path(args[0]);
        if (path.is_relative()) {
            path = fs::current_path() / path; 
        }
        try {
            fs::current_path(path);
        } catch (fs::filesystem_error& e) {
            std::cerr << "cd: " << e.what() << std::endl;
            return -1;
        }
    }
    return 0;
}
