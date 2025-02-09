#include "TypeCommand.hpp"
#include "../CommandManager.hpp"

extern CommandManager globalCommandManager;

int TypeCommand::execute(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); i++) {
        bool isBuiltIn = globalCommandManager.commandExists(args[i]);
        if (isBuiltIn) {
            std::cout << args[i] << " is a built-in command.\n";
        }
        else if(globalCommandManager.ProgramLookup(args[i]).size() != 0) {
            std::string programPath = globalCommandManager.ProgramLookup(args[i]);
            std::cout << args[i] << " is " << programPath << "\n";
        }
        else {
            std::cout << args[i] << " not found.\n";
        }
    }
    return 0;
}
