#ifndef TLB_LOGGER_H_
#define TLB_LOGGER_H_

#include <iostream>
#include <fstream>
#include "date_time.h"

class Logger
{
    private:
        std::ofstream output_file;
        DateTime datetime;

    public:
        Logger(std::string filename);
        void write(std::string message);
        void close();
};


#endif
