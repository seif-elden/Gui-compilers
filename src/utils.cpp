// utils.cpp
#include "utils.h"
#include <fstream>
#include <sstream>

std::string readFile(const std::string &filename)
{
    std::ifstream fileStream(filename);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}