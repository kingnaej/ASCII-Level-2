#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>

int main()
{
    if (std::filesystem::path const dataPath = "../../data"; std::filesystem::exists(dataPath))
    {
        std::unordered_map<char, std::filesystem::path> asciiFile;
        asciiFile[' '] = "../../data/espace.txt";
        for (auto const &folder : std::filesystem::directory_iterator(dataPath))
        {
            if (std::filesystem::is_directory(folder))
            {
                for (const auto &file : std::filesystem::directory_iterator(folder))
                {
                    if (!std::filesystem::is_directory(file) == true && std::filesystem::path(file).extension() == ".txt")
                    {
                        asciiFile[file.path().stem().string()[0]] = file.path();
                    }
                }
            }
        }

        std::string firstTest;
        std::cout << "Ecrivez quelque chose (uniquement lettres et chiffres)\nEvitez les caracteres speciaux et les symboles (+, -, @, &, etc.) : ";
        std::getline(std::cin, firstTest);
        std::cout << std::endl;

        for (auto &content : firstTest) {
            content = static_cast<char>(std::toupper(static_cast<unsigned char>(content)));
            if (asciiFile.contains(content)) {
                if (std::ifstream testFile = asciiFile.at(content); testFile.is_open()) {
                    std::string line;
                    while (std::getline(testFile, line)) {
                        std::cout << line << std::endl;
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "The path: " << dataPath << " does not exist." << std::endl;
    }

    return 0;
}