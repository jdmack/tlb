#include <iostream>
#include <fstream>
#include <sstream>

#include "utils/logger.h"
#include "utils/date_time.h"

/*
Logger::Logger(std::string filename)
{
    output_file.open(filename.c_str());
}
*/

namespace Logger
{
    std::ofstream output_file;
    std::stringstream ss;
}

void Logger::open(std::string filename)
{
    Logger::output_file.open(filename.c_str());
}

void Logger::write(std::string message)
{
    DateTime datetime;
    //Logger::output_file << datetime.timestamp() + message + "\n";
    Logger::output_file << "  " + message + "\n";
    Logger::output_file.flush();
}

void Logger::write(std::basic_ostream<char>& message)
{
    DateTime datetime;
    //Logger::output_file << datetime.timestamp() << ss.str() << "\n";
    Logger::output_file << "  " << ss.str() << "\n";
    Logger::output_file.flush();
    Logger::ss.str(std::string());
}

void Logger::close()
{
    Logger::output_file.close();
}
