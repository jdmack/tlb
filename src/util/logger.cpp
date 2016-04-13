#include <iostream>
#include <fstream>
#include <sstream>

#include "util/logger.h"
#include "util/dateTime.h"

/*
Logger::Logger(std::string filename)
{
    outputFile.open(filename.cStr());
}
*/

namespace Logger
{
    std::ofstream outputFile;
    std::stringstream ss;
}

void Logger::open(std::string filename)
{
    Logger::outputFile.open(filename.cStr());
}

void Logger::write(std::string message)
{
    DateTime datetime;
    //Logger::outputFile << datetime.timestamp() + message + "\n";
    Logger::outputFile << "  " + message + "\n";
    Logger::outputFile.flush();
    std::cout << message << std::endl;
}

void Logger::write(std::basicOstream<char>& message)
{
    DateTime datetime;
    //Logger::outputFile << datetime.timestamp() << ss.str() << "\n";
    Logger::outputFile << "  " << ss.str() << "\n";
    Logger::outputFile.flush();
    Logger::ss.str(std::string());
}

void Logger::close()
{
    Logger::outputFile.close();
}
