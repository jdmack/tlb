////////////////////////////////////////////////////////////////////////////////
//  Header Files
////////////////////////////////////////////////////////////////////////////////

// Standard Library
#include <iostream>
#include <string>

// Third Party Libraries
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

// Project Files
#include "constants.h"
#include "main.h"
#include "screen.h"
#include "timer.h"
#include "dot.h"

int main(int argc, char* args[])
{
    Screen screen;
    if(screen.init() == false) {
        return 1;
    }

    Timer delta_timer;
    SDL_Event event;

    bool quit = false;

    // Create a dot
    Dot dot;

    delta_timer.start();

    // Main Loop
    while(quit == false) {

        // Handle Events
        while(SDL_PollEvent(&event)) {

            // Window close
            if(event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }

            // Keyboard input
            else if((event.type == SDL_KEYDOWN) || (event.type == SDL_KEYUP)) {
                dot.handle_input(event);
            }

        }

        // Update
        dot.move(delta_timer.get_ticks());

        delta_timer.start();

        // Draw
        screen.clear();
        dot.show(screen);

        //screen.blit_surface(game);

        if(!screen.update()) {
            return 1;
        }
    }

    //Clean up
    screen.clean_up();

    return 0;
}
