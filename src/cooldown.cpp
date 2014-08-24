
#include "cooldown.h"

Cooldown::Cooldown()
{
    length_ = 0;
}
// TODO(2014-08-21/JM): When you implement a pause button, you need to deal with all timers

Cooldown::Cooldown(double length)
{
    length_ = length;
}

void Cooldown::start()
{
    timer_.start();
}

void Cooldown::reset()
{
    timer_.start();
}

bool Cooldown::ready()
{
    if(is_running()) {
        if(is_complete()) {
            return true;
        }
        return false;
    }
    return true;
}

bool Cooldown::is_complete()
{
    if(timer_.get_ticks() >= length_) {
        return true;
    }
    return false;
}

bool Cooldown::is_running()
{
    return timer_.started();
}
