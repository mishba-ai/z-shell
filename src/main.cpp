#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unistd.h> // For chdir()

//https://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/#google_vignette 
// https://chat.deepseek.com/a/chat/s/9e0487cf-ed37-4939-bd1d-5acf95fc5110


// Better command handling using enumeration
enum Command {
    CMD_ECHO,
    CMD_CD,
    CMD_EXIT,
    CMD_INVALID,
    CMD_EXTERNAL // For handling external commands later
};

// Function prototype declarations
Command parse_command(const std::string& input);
void execute_command(Command cmd, const std::vector<std::string>& tokens);

int main() {
    std::cout << std::unitbuf; // Auto-flush output
    std::cerr << std::unitbuf;

    std::string input;
    
    while(true) {
        // Display prompt with current directory
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        std::cout << "\033[1;32m" << cwd << "\033[0m $ ";
        
        // Read input
        if(!std::getline(std::cin, input)) {
            break; // Handle Ctrl+D
        }
        
        // Tokenize input
        std::istringstream iss(input);
        std::vector<std::string> tokens{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };
        
        if(tokens.empty()) continue;
        
        // Parse and execute
        Command cmd = parse_command(tokens[0]);
        execute_command(cmd, tokens);
    }
    
    return 0;
}

Command parse_command(const std::string& command) {
    if(command == "echo") return CMD_ECHO;
    if(command == "cd") return CMD_CD;
    if(command == "exit") return CMD_EXIT;
    return CMD_INVALID;
}

void execute_command(Command cmd, const std::vector<std::string>& tokens) {
    switch(cmd) {
        case CMD_ECHO:
            for(size_t i = 1; i < tokens.size(); ++i) {
                std::cout << tokens[i] << " ";
            }
            std::cout << "\n";
            break;
            
        case CMD_CD: {
            std::string path = tokens.size() > 1 ? tokens[1] : getenv("HOME");
            if(chdir(path.c_str()) != 0) {
                std::cerr << "cd: " << path << ": No such directory\n";
            }
            break;
        }
            
        case CMD_EXIT:
            exit(0);
            
        case CMD_INVALID:
            std::cout << tokens[0] << ": command not found\n";
            break;
    }
}