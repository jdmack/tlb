#include <iostream>
#include <fstream>

#include "logger.h"

Logger::Logger()
{
    output_file.open("tlb_log.txt");
}

void Logger::write(std::string message)
{
    output_file << message + "\n";
    output_file.flush();
}

void Logger::close()
{
    output_file.close();
}
