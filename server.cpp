#include <iostream>
#include <fstream>
#include <thread>

int main()
{
    std::cout << "Server ON" << std::endl;
    while (true)
    {
        std::ifstream lockfile("lockfile.txt");
        if (!lockfile.is_open())
        {
            std::cout << "Server is available" << std::endl;
            lockfile.close();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            std::ifstream bufforFile("buffor.txt");
            std::string outputFileName;
            std::string line;
            std::getline(bufforFile, outputFileName);
            std::ofstream outputFile(outputFileName);

            while (std::getline(bufforFile, line))
            {
                std::cout << line << std::endl;
            }
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
            bufforFile.close();
            outputFile.close();
            lockfile.close();
            remove("lockfile.txt");
        }
    }

    return 0;
}