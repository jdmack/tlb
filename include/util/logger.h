#ifndef TLB_LOGGER_H_
#define TLB_LOGGER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "dateTime.h"

namespace Logger
{
    extern std::stringstream ss;
    void open(std::string filename);
    void write(std::string message);
    void write(std::basicOstream<char>&);
    void close();
}


#endif
