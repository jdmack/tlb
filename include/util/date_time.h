#ifndef UTIL_DATE_TIME_H_
#define UTIL_DATE_TIME_H_

#include <ctime>
#include <string>

class DateTime
{
    private:
        timeT time_;
    public:
        DateTime();
        std::string timestamp();
};

#endif
