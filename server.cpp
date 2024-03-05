#include <iostream>
#include <fstream>
#include <thread>

int main()
{
    std::cout << "Server ON" << std::endl;
    while (true)
    {
        // std::cout << "Server is waiting for a client" << std::endl;
        if (std::ifstream("buffor.txt").is_open())
        {
            std::ifstream file("buffor.txt");
            std::string line;
            std::string outputFileName;
            if (std::getline(file, outputFileName))
            {
                std::ofstream outputFile(outputFileName);

                while (std::getline(file, line))
                {
                    std::cout << line << std::endl;
                }

                while (true)
                {
                    std::cout << "Enter your text (type \'exit\' to leave the program)" << std::endl;
                    std::getline(std::cin, line);
                    if (line == "exit")
                    {
                        break;
                    }
                    outputFile << line << "\n";
                }
                outputFile.close();
                file.close();
                std::remove("buffor.txt");
            }
        }
        else
        {
            std::cout << "Server is available" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;
}