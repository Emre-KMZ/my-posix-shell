#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "CommandManager.hpp"

int main() {
  // flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input, arg, command;
  std::vector<std::string> args;
  int exitCode;
  CommandManager commandManager;

  while (true) {
    std::cout << "$ ";
    std::getline(std::cin, input);
    
    args.clear();
    
    std::istringstream ss(input);

    // parse input into command and arguments
    ss >> command;
    while (ss >> arg) {
      args.push_back(arg);
    }

    exitCode = commandManager.executeCommand(command, args);
    if (command == "exit") {
      return exitCode;
    }
    
  }


  return 0; 
}


