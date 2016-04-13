#include "util/timer.h"
#include "util/globalTimer.h"

Timer::Timer()
{
    // Initialize the variables
    startTicks_ = 0;
    pausedTicks_ = 0;
    paused_ = false;
    started_ = false;
}

void Timer::start()
{
    // Start the timer
    started_ = true;

    // Unpause the timer
    paused_ = false;

    // Get the current clock time
    startTicks_ = GlobalTimer::instance()->getTicks();
}

void Timer::stop()
{
    // Stop the timer
    started_ = false;

    // Unpause the timer
    paused_ = false;
}

void Timer::pause()
{
    // If the timer is running and isn't already paused_
    if((started_ == true) && (paused_ == false)) {
        // Pause the timer
        paused_ = true;

        // Calculate the paused_ ticks
        pausedTicks_ = GlobalTimer::instance()->getTicks() - startTicks_;
    }
}

void Timer::unpause()
{
    // If the timer is paused_
    if(paused_ == true) {
        // Unpause the timer
        paused_ = false;

        // Reset the starting ticks
        startTicks_ = GlobalTimer::instance()->getTicks() - pausedTicks_;

        // Reset the paused_ ticks
        pausedTicks_ = 0;
    }
}

int Timer::getTicks()
{
    // If the timer is running
    if(started_ == true) {
        // If the timer is paused_
        if(paused_ == true) {
            // Return the number of ticks when the timer was paused_
            return pausedTicks_;
        }
        else {
            // Return the current time minus the start time
            return GlobalTimer::instance()->getTicks() - startTicks_;
        }
    }

    // If the timer isn't running
    return 0;
}
