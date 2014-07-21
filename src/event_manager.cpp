/* Event Agent */

#include <vector>
#include "SDL2/SDL.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "game.h"
#include "game_object.h"
#include "utils/logger.h"
#include "point.h"
#include "entity.h"
#include "camera.h"

EventManager::EventManager(Game * game)
{
    game_ = game;
}

void EventManager::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        // timer checks
        if((focus_timer_.started()) && (focus_timer_.get_ticks() >= kFocusTimeout)) {
            game_->set_quit(true);
            Logger::write("Setting game quit");
        }

        // Handle Events
        switch(event.type) {
            case SDL_QUIT:  // Quit Event (user x's the window)
                game_->set_quit(true);
                break;

            case SDL_KEYDOWN:   // Keypress
                switch(event.key.keysym.sym) {

                    case SDLK_ESCAPE:   // Escape
                        game_->set_quit(true);
                        break;

                    case SDLK_s:    // S
                        if(!game_->entity_manager()->selected()->empty()) {
                            // something is selected, can now give it an order
                            std::vector<GameObject *> * selected = game_->entity_manager()->selected();
                            for(std::vector<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator < selected->end(); ++selected_iterator) {
                                //(*selected_iterator)->stop();
                                // TODO(2014-01-23/JM): Fix stop
                            }
                        }
                        break;

                    case SDLK_UP:       // Up Arrow
                        break;
                    case SDLK_DOWN:     // Down Arrow
                        break;
                    case SDLK_LEFT:     // Left Arrow
                        break;
                    case SDLK_RIGHT:    // Right Arrow
                        break;
                }
                break;

            case SDL_KEYUP:
                switch( event.key.keysym.sym) {
                    case SDLK_UP:       // Up Arrow
                        break;
                    case SDLK_DOWN:    // Down Arrow
                        break;
                    case SDLK_LEFT:    // Left Arrow
                        break;
                    case SDLK_RIGHT:    // Right Arrow
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN: {
                // mouse Points adjusted to camera position
                int mouse_x = event.button.x + game_->camera()->x_position();
                int mouse_y = event.button.y + game_->camera()->y_position();

                // SDL_BUTTON_LEFT - Selection
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // 2 cases
                    GameObject * clicked_on = game_->entity_manager()->get_object_at(mouse_x, mouse_y);
                    // 1. clicking on nothing
                    if(clicked_on == nullptr) {
                        // NOTE: left clicking on anything deselects_all with current functionality
                        game_->entity_manager()->deselect_all();
                    }
                    // 2. clicking on something
                    else {
                        if(!clicked_on->selected() || game_->entity_manager()->objects()->size() != 1) {
                            game_->entity_manager()->deselect_all();
                            game_->entity_manager()->select(clicked_on);
                        }
                    }

                }
                // SDL_BUTTON_RIGHT - Command
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    if(!game_->entity_manager()->selected()->empty()) {
                        // something is selected, can now give it an order
                        std::vector<GameObject *> * selected = game_->entity_manager()->selected();
                        for(std::vector<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator < selected->end(); ++selected_iterator) {
                            (*selected_iterator)->move(mouse_x, mouse_y);
                        }
                    }
                }
                break;
            }
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    focus_timer_.start();
                    //Logger::write("focus_timer started");
                }
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    if(focus_timer_.started()) {
                        focus_timer_.stop();
                        //Logger::write("focus_timer stopped");
                    }
                }
                break;
        }
    }
}

Point EventManager::mouse_position()
{
    int x, y = 0;
    SDL_GetMouseState(&x, &y);
    return Point(x, y);
}
