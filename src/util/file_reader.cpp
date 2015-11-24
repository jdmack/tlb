#include "util/file_reader.h"

#include <string>
#include <iostream>
#include <fstream>

std::string FileReader::read_file(const char * filename)
{
    std::string content;

    std::ifstream file_stream(filename, std::ios::in);

    if(!file_stream.is_open()) {
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!file_stream.eof()) {
        std::getline(file_stream, line);
        content.append(line + "\n");
    }

    file_stream.close();
    return content;
}
