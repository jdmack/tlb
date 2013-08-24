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

int main(int argc, char* args[])
{
    Screen screen;
    if(screen.init() == false) {
        return 1;
    }

    SDL_Event event;

    bool quit = false;

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

        }


        // Update
        //myDot.move(delta.get_ticks());

        // Draw
        screen.clear();
        //screen.blit_surface(game);

        if(!screen.update()) {
            return 1;
        }
    }

    //Clean up
    screen.clean_up();

    return 0;
}
