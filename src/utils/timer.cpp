#include "SDL/SDL.h"
#include "utils/timer.h"

Timer::Timer()
{
    // Initialize the variables
    start_ticks_ = 0;
    paused_ticks_ = 0;
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
    start_ticks_ = SDL_GetTicks();
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
        paused_ticks_ = SDL_GetTicks() - start_ticks_;
    }
}

void Timer::unpause()
{
    // If the timer is paused_
    if(paused_ == true) {
        // Unpause the timer
        paused_ = false;

        // Reset the starting ticks
        start_ticks_ = SDL_GetTicks() - paused_ticks_;

        // Reset the paused_ ticks
        paused_ticks_ = 0;
    }
}

int Timer::get_ticks()
{
    // If the timer is running
    if(started_ == true) {
        // If the timer is paused_
        if(paused_ == true) {
            // Return the number of ticks when the timer was paused_
            return paused_ticks_;
        }
        else {
            // Return the current time minus the start time
            return SDL_GetTicks() - start_ticks_;
        }
    }

    // If the timer isn't running
    return 0;
}
