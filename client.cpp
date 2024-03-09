#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{
    std::cout << "Client ON" << std::endl;

    if (argc != 2)
    {
        std::cout << "Too many arguments used" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ofstream outputFile("buffor.txt");
    outputFile << filename << "\n";
    while (true)
    {
        std::cout << "Enter your text (type \'exit\' to leave the program)" << std::endl;
        std::string line;
        std::getline(std::cin, line);
        if (line == "exit")
        {
            break;
        }
        outputFile << line << "\n";
    }
    outputFile.close();

    while (true)
    {
        std::ifstream lockfile("lockfile.txt");
        if (!lockfile.is_open())
        {
            std::ofstream lockfile("lockfile.txt");
            lockfile.close();
            break;
        }
        else
        {
            std::cout << "Server is occupied, please wait" << std::endl;
            lockfile.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}