#include <iostream>
#include <string>

//https://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/#google_vignette

int main() {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;

    // A REPL is an interactive loop that reads user input, evaluates it, prints the result, and then waits for the next input
    while (true) {
        std::cout << "$ ";  // Display the prompt
        std::getline(std::cin, input);  // Read the command
        
        // Check if input is empty (user just pressed Enter)
        if (input.empty()) {
            continue;  // Skip processing if no command was entered
        }

        if(input == "exit 0") {
      exit(0);
    }

        // Display command not found message
        std::cout << input << ": command not found" << std::endl; 
    }

    return 0; // This line will never be reached due to the infinite loop
}
