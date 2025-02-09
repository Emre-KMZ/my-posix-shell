#include "ExitCommand.hpp"


int ExitCommand::execute(const std::vector<std::string>& args) {
    if (!args.empty()) {
        try {
            short exit_code = std::stoi(args[1]);
            std::cout << "Exiting with code " << exit_code << ".\n";
            return exit_code;
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid exit code: " << args[1] << ". Exiting with code 1.\n";
            return 1; // default exit code for invalid input
        } catch (const std::out_of_range&) {
            std::cerr << "Exit code out of range: " << args[1] << ". Exiting with code 1.\n";
            return 1; // default exit code if number is too large
        }
    }
    return 0;
}
