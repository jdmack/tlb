#ifndef TLB_LOGGER_H_
#define TLB_LOGGER_H_

#include <iostream>
#include <fstream>

class Logger
{
    private:
        std::ofstream output_file;

    public:
        Logger();
        void write(std::string message);
        void close();
};


#endif
