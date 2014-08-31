#include "SDL2/SDL.h"
#include "util/global_timer.h"
#include "util/logger.h"

GlobalTimer * GlobalTimer::instance_;

GlobalTimer::GlobalTimer()
{
    // Initialize the variables
    start_ticks_ = 0;
    paused_ticks_ = 0;
    paused_ = false;
    started_ = false;
    instance_ = nullptr;
}

GlobalTimer * GlobalTimer::instance()
{
    if(instance_ == nullptr) {
        instance_ = new GlobalTimer();
    }
    return instance_;
}


void GlobalTimer::start()
{
    // Start the timer
    started_ = true;

    // Unpause the timer
    paused_ = false;

    // Get the current clock time
    start_ticks_ = SDL_GetTicks();
}

void GlobalTimer::stop()
{
    // Stop the timer
    started_ = false;

    // Unpause the timer
    paused_ = false;
}

void GlobalTimer::pause()
{
    // If the timer is running and isn't already paused_
    if((started_ == true) && (paused_ == false)) {
        // Pause the timer
        paused_ = true;

        // Calculate the paused_ ticks
        paused_ticks_ = SDL_GetTicks() - start_ticks_;
    }
}

void GlobalTimer::unpause()
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

void GlobalTimer::toggle_pause()
{
    if(paused_) {
        Logger::write("Un-Pausing");
        unpause();
    }
    else {
        Logger::write("Pausing");
        pause();
    }
}

int GlobalTimer::get_ticks()
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
