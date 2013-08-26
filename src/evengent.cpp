/* Event Agent */

#include "SDL/SDL.h"
#include "evengent.h"
#include "entigent.h"
#include "tlb_game.h"

Evengent::Evengent()
{
    game_ = nullptr;
}

void Evengent::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_QUIT:
                game_->set_quit(true);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                game_->set_quit(true);
                }
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEBUTTONDOWN:
                // SDL_BUTTON_LEFT
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // 2 cases
                    // 1. clicking on something
                    GameObject * clicked_on = game_->entigent()->get_object_at(event.button.x, event.button.y);
                    // 2. clicking on nothing
                    if(clicked_on == nullptr) {

                    }

                }
                // SDL_BUTTON_RIGHT
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {

                }
                break;

        }
    }
}

void Evengent::register_game(TlbGame * game)
{
    game_ = game;
}
