#ifndef TLB_LOGGER_H_
#define TLB_LOGGER_H_

#include <iostream>
#include <fstream>
#include "date_time.h"

namespace Logger
{
    void open(std::string filename);
    void write(std::string message);
    void close();
};


#endif
