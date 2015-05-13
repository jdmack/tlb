
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
#include "gfx/camera.h"
#include "util/math.h"
#include "action/rotate_action.h"
#include "util/global_timer.h"
#include "event/event.h"
#include "event/event_dispatcher.h"
#include "event/e_key_press.h"
#include "event/e_mouse_click.h"

EventManager::EventManager()
{

}

void EventManager::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        const Uint8 * current_key_states = SDL_GetKeyboardState(NULL);
        // timer checks
        if((focus_timer_.started()) && (focus_timer_.get_ticks() >= kFocusTimeout)) {
            Game::instance()->set_quit(true);
            Logger::write("Setting game quit");
        }

        // Handle Events
        switch(event.type) {
            case SDL_QUIT:  // Quit Event (user x's the window)
                Game::instance()->set_quit(true);
                break;

            case SDL_KEYDOWN:   // Keypress
                KeyType key;
                switch(event.key.keysym.sym) {

                    case SDLK_ESCAPE:   // Escape
                        key = KEY_ESCAPE;
                        break;
                    case SDLK_a:    // A
                        key = KEY_A;
                        break;
                    case SDLK_r:    // R
                        key = KEY_R;
                        break;
                    case SDLK_s:    // S
                        key = KEY_S;
                        break;
                    case SDLK_UP:       // Up Arrow
                        key = KEY_UP;
                        break;
                    case SDLK_DOWN:     // Down Arrow
                        key = KEY_DOWN;
                        break;
                    case SDLK_LEFT:     // Left Arrow
                        key = KEY_LEFT;
                        break;
                    case SDLK_RIGHT:    // Right Arrow
                        key = KEY_RIGHT;
                        break;
                    case SDLK_SPACE:    // Spacebar
                        key = KEY_SPACE;
                        break;
                }
                EventDispatcher::instance()->send_event(new EKeyPress(key));
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

            case SDL_MOUSEBUTTONDOWN:
                // mouse Points adjusted to camera position
                double mouse_x = event.button.x + Game::instance()->camera()->x_position();
                double mouse_y = event.button.y + Game::instance()->camera()->y_position();

                Point mouse_point = Point(mouse_x, mouse_y);
                mouse_point = Math::convert_to_cartesian(mouse_point);

                mouse_x = mouse_point.x();
                mouse_y = mouse_point.y();

                //Logger::write(Logger::ss << "mouse: (" << mouse_x << "," << mouse_y << ")");

                EMouseClick * mouse_event;

                // SDL_BUTTON_LEFT - Selection
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouse_event = new EMouseClick(MOUSE_LEFT, mouse_point);
                }
                // SDL_BUTTON_RIGHT - Command
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouse_event = new EMouseClick(MOUSE_RIGHT, mouse_point);
                }

                EventDispatcher::instance()->send_event(mouse_event);

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
