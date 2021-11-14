#include "ReadFile.h"


std::string ReadFile::ReadAndReturnContent(std::string filePath) {
    std::string content = "";
    std::ifstream file(filePath.c_str(), std::ios::in);
    if (file.good()) {
        if (file.is_open()) {
            std::string line = "";
            while (std::getline(file, line))
            {
                content.append(line + "\n");
            }
            file.close();
        } else {
            std::cout << "\033[1;31m" << "Error opening file : " << filePath << "\033[0m" << std::endl;// rouge gras
        }
    } else {
        std::cout << "\033[1;31m" << "File not exist ! " << filePath << "\033[0m" << std::endl;// rouge gras
    }
    return content;
}
