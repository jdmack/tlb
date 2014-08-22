
#include "cooldown.h"

Cooldown::Cooldown()
{
    duration_ = 0;
}
// TODO(2014-08-21/JM): When you implement a pause button, you need to deal with all timers

Cooldown::Cooldown(double duration)
{
    duration_ = duration;
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
    if(timer_.get_ticks() >= duration_) {
        return true;
    }
    return false;
}

bool Cooldown::is_running()
{
    return timer_.started();
}
