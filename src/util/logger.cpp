#include <iostream>
#include <fstream>
#include <sstream>

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
    std::stringstream string_stream;
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

void Logger::write(std::basic_ostream<char>& message)
{
    DateTime datetime;
    Logger::output_file << datetime.timestamp() << string_stream.str() << "\n";
    Logger::output_file.flush();
    Logger::string_stream.str(std::string());
}

void Logger::close()
{
    Logger::output_file.close();
}
