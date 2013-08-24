
#include "SDL/SDL.h"

// Project Files
#include "tlb_game.h"
#include "dot.h"
#include "assets.h"

TlbGame::TlbGame()
{
    exit_code_ = 0;
    quit_ = false;
}

int TlbGame::run()
{
    if(screen_.init() == false) {
        return 1;
    }

    delta_timer_.start();

    game_loop();

    //Clean up
    screen_.clean_up();

    return exit_code_;
}

void TlbGame::game_loop()
{
    // Create a dot
    Dot dot(kAssetArtDot);

    // Main Loop
    while(quit_ == false) {

        // Handle Events
        while(SDL_PollEvent(&event_)) {

            if(event_.type == SDL_QUIT) {
                //Quit the program
                quit_ = true;
            }

            // Keyboard input
            else if((event_.type == SDL_KEYDOWN) || (event_.type == SDL_KEYUP)) {
                dot.handle_input(event_);
            }

        }

        // Update
        dot.move(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_.clear();
        dot.draw(screen_);

        //screen_.blit_surface(game);

        if(!screen_.update()) {
            exit_code_ = 1;
        }
    }

}

// placeholder functions (not implemented yet)

void TlbGame::process_arguments(int argc, char * argv[])
{

}
