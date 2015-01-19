
#include <list>
#include "SDL2/SDL.h"
#include "event_manager.h"
#include "entity_manager.h"
#include "gs_level.h"
#include "game.h"
#include "game_object.h"
#include "util/logger.h"
#include "point.h"
#include "entity.h"
#include "camera.h"
#include "util/math.h"
#include "action/rotate_action.h"
#include "util/global_timer.h"

EventManager::EventManager(Game * game)
{
    game_ = game;
}

void EventManager::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        const Uint8 * current_key_states = SDL_GetKeyboardState(NULL);
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
                            std::list<GameObject *> * selected = game_->entity_manager()->selected();
                            for(std::list<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator != selected->end(); ++selected_iterator) {

                                GameObject * object = *selected_iterator;
                                if(object->is_entity()) {
                                    Entity * entity = static_cast<Entity *>(object);
                                    entity->stop();
                                }
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
                    case SDLK_SPACE:    // Spacebar
                        GlobalTimer::instance()->toggle_pause();
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
                double mouse_x = event.button.x + game_->camera()->x_position();
                double mouse_y = event.button.y + game_->camera()->y_position();

                Point mouse_point = Point(mouse_x, mouse_y);
                mouse_point = Math::convert_to_cartesian(mouse_point);

                mouse_x = mouse_point.x();
                mouse_y = mouse_point.y();

                //Logger::write(Logger::ss << "mouse: (" << mouse_x << "," << mouse_y << ")");

                // SDL_BUTTON_LEFT - Selection
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    // Check if an entity is selected and R is being held down
                    //if(!game_->entity_manager()->selected()->empty()) {
                        if(current_key_states[SDL_SCANCODE_R]) {
                            std::list<GameObject *> * selected = game_->entity_manager()->selected();
                            for(std::list<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator != selected->end(); ++selected_iterator) {
                                GameObject * object = *selected_iterator;
                                if(object->is_entity()) {
                                    Entity * entity = static_cast<Entity *>(object);
                                    entity->rotate(mouse_point);
                                }
                            }

                        }
                        else if(current_key_states[SDL_SCANCODE_A]) {
                            std::list<GameObject *> * selected = game_->entity_manager()->selected();
                            for(std::list<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator != selected->end(); ++selected_iterator) {
                                GameObject * object = *selected_iterator;
                                if(object->is_entity()) {
                                    Entity * entity = static_cast<Entity *>(object);

                                    GameObject * target_object = game_->entity_manager()->get_object_at(mouse_x, mouse_y);

                                    if((target_object != nullptr) && (target_object->is_entity())) {
                                        Entity * target_entity = static_cast<Entity *>(target_object);
                                        entity->attack(target_entity);
                                    }
                                }
                            }

                        }
                    //}
                    else {
                        // 2 cases
                        GameObject * clicked_on = game_->entity_manager()->get_object_at(mouse_x, mouse_y);
                        // 1. clicking on nothing
                        if(clicked_on == nullptr) {
                            // NOTE: left clicking on anything deselects_all with current functionality
                            Logger::write("Deselecting");
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

                }
                // SDL_BUTTON_RIGHT - Command
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    if(!game_->entity_manager()->selected()->empty()) {
                        // something is selected, can now give it an order
                        std::list<GameObject *> * selected = game_->entity_manager()->selected();
                        for(std::list<GameObject *>::iterator selected_iterator = selected->begin(); selected_iterator != selected->end(); ++selected_iterator) {

                            Point mouse_point = Point(mouse_x, mouse_y);

                            if(Game::instance()->state()->type() == GS_LEVEL) {
                                GSLevel * state = static_cast<GSLevel *>(Game::instance()->state());
                                mouse_point = Point(mouse_x - state->level_area()->x(), mouse_y - state->level_area()->y());
                            }

                            (*selected_iterator)->move(mouse_point);
                        }
                    }
                }
                break;
            }
/*
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
                */
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
