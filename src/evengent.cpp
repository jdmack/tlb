/* Event Agent */

#include <vector>
#include "SDL/SDL.h"
#include "evengent.h"
#include "entigent.h"
#include "tlb_game.h"
#include "game_object.h"
#include "util/logger.h"

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
                // SDL_BUTTON_LEFT - Selection
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // 2 cases
                    GameObject * clicked_on = game_->entigent()->get_object_at(event.button.x, event.button.y);
                    // 1. clicking on nothing
                    if(clicked_on == nullptr) {
                        // NOTE: left clicking on anything deselects_all with current functionality
                        game_->entigent()->deselect_all();
                    }
                    // 2. clicking on something
                    else {
                        if(!clicked_on->selected() || game_->entigent()->objects()->size() != 1) {
                            game_->entigent()->deselect_all();
                            game_->entigent()->select(clicked_on);
                        }
                    }

                }
                // SDL_BUTTON_RIGHT - Command
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    if(!game_->entigent()->selected()->empty()) {
                        // something is selected, can now give it an order
                        std::vector<GameObject *> * selected = game_->entigent()->selected();
                        for(std::vector<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator < selected->end(); ++selected_iterator) {
                            (*selected_iterator)->move(event.button.x, event.button.y);
                        }
                    }
                }
                break;

        }
    }
}
