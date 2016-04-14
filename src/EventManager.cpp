
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
#include "util/math/Math.h"
#include "action/RotateAction.h"
#include "util/GlobalTimer.h"
#include "event/Event.h"
#include "event/EventDispatcher.h"
#include "event/EKeyPress.h"
#include "event/EMouseClick.h"

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
                Game::instance()->setQuit(true);
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
                // mouse Points adjusted to camera position
                double mouseX = event.button.x + Game::instance()->camera()->xPosition();
                double mouseY = event.button.y + Game::instance()->camera()->yPosition();

                Point mousePoint = Point(mouseX, mouseY);
                mousePoint = Math::convertToCartesian(mousePoint);

                mouseX = mousePoint.x();
                mouseY = mousePoint.y();

                //Logger::write(Logger::ss << "mouse: (" << mouseX << "," << mouseY << ")");

                EMouseClick * mouseEvent;

                // SDL_BUTTON_LEFT - Selection
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseEvent = new EMouseClick(MOUSE_LEFT, mousePoint);
                }
                // SDL_BUTTON_RIGHT - Command
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseEvent = new EMouseClick(MOUSE_RIGHT, mousePoint);
                }

                EventDispatcher::instance()->sendEvent(mouseEvent);

/*
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                    focusTimer_.start();
                    //Logger::write("focusTimer started");
                }
                if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                    if(focusTimer_.started()) {
                        focusTimer_.stop();
                        //Logger::write("focusTimer stopped");
                    }
                }
                */
                break;
        }
    }
}

Point EventManager::mousePosition()
{
    int x, y = 0;
    SDL_GetMouseState(&x, &y);
    return Point(x, y);
}
