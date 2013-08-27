#include <iostream>
#include <fstream>

#include "util/logger.h"
#include "util/date_time.h"

/*
Logger::Logger(std::string filename)
{
    output_file.open(filename.c_str());
}
*/

namespace Logger
{
    std::ofstream output_file;
}

void Logger::open(std::string filename)
{
    Logger::output_file.open(filename.c_str());
}

void Logger::write(std::string message)
{
    DateTime datetime;
    Logger::output_file << datetime.timestamp() + message + "\n";
    Logger::output_file.flush();
}

void Logger::close()
{
    Logger::output_file.close();
}
