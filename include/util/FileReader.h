#ifndef TLB_UTIL_FILE_READER_H_
#define TLB_UTIL_FILE_READER_H_

#include <string>

class FileReader
{
    public:
        static bool readFile(const char *filename, std::string content);
    
};

#endif
