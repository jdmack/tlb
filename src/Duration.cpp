
#include "Duration.h"

Duration::Duration()
{
    length_ = 0;
}
// TODO(2014-08-21/JM): When you implement a pause button, you need to deal with all timers

Duration::Duration(double length)
{
    length_ = length;
}

void Duration::start()
{
    timer_.start();
}

void Duration::reset()
{
    timer_.start();
}

bool Duration::isComplete()
{
    if(timer_.getTicks() >= length_) {
        return true;
    }
    return false;
}
