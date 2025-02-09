#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "CommandManager.hpp"
#include <filesystem>


CommandManager globalCommandManager; 

int main() {
  // flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input, arg;
  std::vector<std::string> args;
  int exitCode;

  while (true) {
    std::string currentPath = std::filesystem::current_path().string();
    std::cout << currentPath.substr(currentPath.find_last_of("/") + 1) << " "; // only print current directory
    std::cout << "$ ";
    std::getline(std::cin, input);
    
    args.clear();
    
    std::istringstream ss(input);

    // parse input into command and arguments
    while (ss >> arg) {
      args.push_back(arg);
    }

    exitCode = globalCommandManager.executeCommand(args);
    if (args[0] == "exit") {
      return exitCode;
    }
    
  }


  return 0; 
}


