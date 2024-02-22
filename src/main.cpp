#include <iostream>
#include <string>

int main()
{
    std::string input;
    while (input != "quit") {
        std::cout << "Enter a string (enter 'quit' to exit): ";
        std::getline(std::cin, input);
    }

    return 0;
}