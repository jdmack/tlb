#include "util/fileReader.h"

#include <string>
#include <iostream>
#include <fstream>

std::string FileReader::readFile(const char * filename)
{
    std::string content;

    std::ifstream fileStream(filename, std::ios::in);

    if(!fileStream.isOpen()) {
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}
