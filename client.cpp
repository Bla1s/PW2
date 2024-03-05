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

    std::string outputFile = argv[1];
    std::string serverBuffor = "buffor.txt";

    std::vector<std::string> lines;
    std::string text;
    while (true)
    {
        std::cout << "Enter your text (type \'exit\' to leave the program)" << std::endl;
        std::getline(std::cin, text);
        if (text == "exit")
        {
            break;
        }
        lines.push_back(text);
    }

    std::stringstream ss;
    ss << outputFile << "\n";
    for (const auto &line : lines)
    {
        ss << line << "\n";
    }

    std::string combined = ss.str();

    std::ifstream file(serverBuffor);
    while (true)
    {
        if (file.is_open())
        {
            std::cout << "Server is occupied, please wait" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            std::cout << "Server is available" << std::endl;
            std::ofstream file(serverBuffor);
            file << combined;
            file.close();
            break;
        }
    }

    return 0;
}