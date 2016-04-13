#include <ctime>
#include <string>

#include "util/dateTime.h"

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
    std::string returnString(s);
    return returnString;
}
