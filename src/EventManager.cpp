
#include <list>
#include "SDL2/SDL.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "GSLevel.h"
#include "Game.h"
#include "GameObject.h"
#include "util/Logger.h"
#include "Point.h"
#include "Entity.h"
#include "gfx/Camera.h"
#include "math/Math.h"
#include "action/RotateAction.h"
#include "util/GlobalTimer.h"
#include "event/Event.h"
#include "event/EventDispatcher.h"
#include "event/EKeyPress.h"
#include "event/EMouse.h"
#include "gfx/Camera.h"
#include "gfx/Renderer.h"

EventManager::EventManager()
{
}

void EventManager::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {

        const Uint8 * currentKeyStates = SDL_GetKeyboardState(NULL);
        // timer checks
        if((focusTimer_.started()) && (focusTimer_.getTicks() >= kFocusTimeout)) {
            Game::instance()->setQuit(true);
            Logger::write("Setting game quit");
        }

        // Handle Events
        switch(event.type) {
            case SDL_QUIT:  // Quit Event (user x's the window)
                EventDispatcher::instance()->sendEvent(new Event(EVENT_GAME_QUIT));

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
                    case SDLK_d:    // D
                        key = KEY_D;
                        break;
                    case SDLK_w:    // W
                        key = KEY_W;
                        break;
                    case SDLK_c:    // C
                        key = KEY_C;
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
                    
                Game::instance()->renderer()->camera()->onKeyboard(key);
                EventDispatcher::instance()->sendEvent(new EKeyPress(key));
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
            {
                Vector2i mousePosition = Vector2i(event.button.x, event.button.y);

                EMouse * mouseEvent;

                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseEvent = new EMouse(MOUSE_BUTTON_LEFT, mousePosition);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseEvent = new EMouse(MOUSE_BUTTON_RIGHT, mousePosition);
                }

                EventDispatcher::instance()->sendEvent(mouseEvent);

                break;
            }
            case SDL_WINDOWEVENT_FOCUS_LOST:
            {
                //focusTimer_.start();
                //Logger::write("focusTimer started");
                //if(focusTimer_.started()) {
                    //focusTimer_.stop();
                    //Logger::write("focusTimer stopped");
                //}
                break;
            }
            case SDL_MOUSEMOTION:
            {
                EMouse * mouseEvent = new EMouse(EVENT_MOUSE_MOTION);
                mouseEvent->setPosition(Vector2i(event.motion.x, event.motion.y));
                EventDispatcher::instance()->sendEvent(mouseEvent);

                break;
            }
        }
    }
}

Point EventManager::mousePosition()
{
    int x, y = 0;
    SDL_GetMouseState(&x, &y);
    return Point(x, y);
}
