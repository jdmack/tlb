
#include "SDL/SDL.h"

// Project Files
#include "tlb_game.h"
#include "dot.h"
#include "assets.h"
#include "screen.h"
#include "logger.h"

TlbGame::TlbGame()
{
    exit_code_ = 0;
    quit_ = false;
    screen_ = new Screen();
}

int TlbGame::run()
{
    logger.write("Run");
    if(screen_->init() == false) {
        return 1;
    }

    delta_timer_.start();

    game_loop();

    //Clean up
    screen_->clean_up();

    logger.close();

    return exit_code_;
}

void TlbGame::game_loop()
{
    // Create a dot
    Dot * dot1 = new Dot(kAssetArtDot);
    screen_->addObject(dot1);

    Dot * dot2 = new Dot(kAssetArtDot, 0, kScreenHeight - kDotHeight);
    screen_->addObject(dot2);

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
                logger.write("SDL_KEYDOWN");
                dot1->handle_input(event_);
                dot2->handle_input(event_);
            }

            // Mouse input
            //else if((event_.type == SDL_MOUSEBUTTONDOWN) || (event_.type == SDL_MOUSEBUTTONUP)) {
            else if(event_.type == SDL_MOUSEBUTTONDOWN) {
                logger.write("SDL_MOUSEBUTTONDOWN");

                if(event_.button.button == SDL_BUTTON_LEFT) {
                    logger.write("SDL_BUTTON_LEFT");
                    // select object
                    if(dot1->contains_point(event_.button.x, event_.button.y)) {
                        dot1->select();
                        dot2->deselect();
                    }
                    else if(dot2->contains_point(event_.button.x, event_.button.y)) {
                        dot2->select();
                        dot1->deselect();
                    }
                    else {
                        dot1->deselect();
                        dot2->deselect();
                    }
                }
                else if(event_.button.button == SDL_BUTTON_RIGHT) {
                    // issue order command
                }
            }

        }

        // Update
        dot1->move(delta_timer_.get_ticks());
        dot2->move(delta_timer_.get_ticks());

        delta_timer_.start();

        // Draw
        screen_->clear();
        dot1->draw(screen_);
        dot2->draw(screen_);

        //screen_->blit_surface(game);

        if(!screen_->update()) {
            exit_code_ = 1;
        }
    }

    delete(dot1);
    delete(dot2);
}

// placeholder functions (not implemented yet)

void TlbGame::process_arguments(int argc, char * argv[])
{

}
