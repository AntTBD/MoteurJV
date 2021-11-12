#pragma once

#include <fstream>
#include <iostream>
#include <string>

class ReadFile {
public:
    static std::string ReadAndReturnContent(std::string filePath);
};
