#include "TypeCommand.hpp"
#include "../CommandManager.hpp"

extern CommandManager globalCommandManager;

int TypeCommand::execute(const std::vector<std::string>& args) {
    // for now, we just have 2 types; invalid and built-in
    for (auto arg : args) {
        bool isBuiltIn = globalCommandManager.commandExists(arg);
        if (isBuiltIn) {
            std::cout << arg << " is a built-in command.\n";
        } else {
            std::cout << arg << " not found.\n";
        }
    }

    return 0;
}
