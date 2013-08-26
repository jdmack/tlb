#include <iostream>
#include <fstream>

#include "logger.h"

Logger::Logger(std::string filename)
{
    output_file.open(filename.c_str());
}

void Logger::write(std::string message)
{
    output_file << datetime.timestamp() + message + "\n";
    output_file.flush();
}

void Logger::close()
{
    output_file.close();
}
