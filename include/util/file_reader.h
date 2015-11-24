#ifndef TLB_UTIL_FILE_READER_H_
#define TLB_UTIL_FILE_READER_H_

#include <string>

class FileReader
{
    public:
        static std::string read_file(const char *filename);
    
};

#endif
