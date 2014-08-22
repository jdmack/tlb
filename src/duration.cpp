
#include "duration.h"

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

bool Duration::is_complete()
{
    if(timer_.get_ticks() >= length_) {
        return true;
    }
    return false;
}
