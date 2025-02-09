#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "CommandManager.hpp"
#include <filesystem>

CommandManager globalCommandManager; 

void extractArgs(const std::string& input, std::vector<std::string>& args) {
  // TODO: Un-closed quotes are not handled, yet

  std::string arg = "";
  bool inDoubleQuote = false;
  bool inSingleQuote = false;

  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == ' ' && !inDoubleQuote && !inSingleQuote) {
      if (arg != "") {
        args.push_back(arg);
        arg = "";
      }
    } else if (input[i] == '\"' && !inSingleQuote) {
      inDoubleQuote = !inDoubleQuote;
    } else if (input[i] == '\'' && !inDoubleQuote) {
      inSingleQuote = !inSingleQuote;
    } else {
      if (input[i] == '\\' || (input[i + 1] == '\"' || input[i + 1] == (char)96 || input[i + 1] == '$')) {
        arg += input[i + 1];
        i++;
      } else {
        arg += input[i];
      }
    }
  }
  if (arg != "") {
    args.push_back(arg);
  }
}

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

    extractArgs(input, args);

    exitCode = globalCommandManager.executeCommand(args);
    if (args[0] == "exit") {
      return exitCode;
    }
    
  }


  return 0; 
}


