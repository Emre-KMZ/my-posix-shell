#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int handle_exit(const std::vector<std::string>& args) {
    if (!args.empty()) {
        try {
            short exit_code = std::stoi(args[0]);
            std::cout << "Exiting with code " << exit_code << ".\n";
            return exit_code;
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid exit code: " << args[0] << ". Exiting with code 1.\n";
            return 1; // default exit code for invalid input
        } catch (const std::out_of_range&) {
            std::cerr << "Exit code out of range: " << args[0] << ". Exiting with code 1.\n";
            return 1; // default exit code if number is too large
        }
    }
    return 0;
}

void handle_echo(const std::vector<std::string>& args) {
    for (const auto& arg : args) {
        std::cout << arg << " ";
    }
    std::cout << std::endl;
}

int main() {
  // flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input, arg, command;
  std::vector<std::string> args;
  

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

    if (command == "exit") {
      return handle_exit(args);
    }
    else if (command == "echo") {
      handle_echo(args);
    }
    else {
      std::cout << input << ": command not found" << std::endl;
    }
  }


  return 0; 
}


