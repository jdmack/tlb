#include <ctime>
#include <string>
#include "date_time.h"

DateTime::DateTime()
{
    time_ = time(NULL);
}

std::string DateTime::timestamp()
{
    char s[1000];

    time_ = time(NULL);
    struct tm * p = localtime(&time_);
    strftime(s, 1000, "[%a %b %d %H:%M:%S %Y] ", p);
    std::string return_string(s);
    return return_string;
}
