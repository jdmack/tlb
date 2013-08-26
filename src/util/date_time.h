#ifndef UTIL_DATE_TIME_H_
#define UTIL_DATE_TIME_H_

#include <ctime>
#include <string>

class DateTime
{
    private:
        time_t time_;
    public:
        DateTime();
        std::string timestamp();

};

#endif
