/* Event Agent */

#ifndef TLB_EVENGENT_H_
#define TLB_EVENGENT_H_

#include "coordinate.h"
#include "timer.h"

class TlbGame;

const double kFocusTimeout = 1000;

class Evengent
{
    private:
        TlbGame * game_;
        Timer focus_timer_;

    public:
        Evengent();
        void handle_events();

        // mutators
        void set_game(TlbGame * game) { game_ = game; }

        static Coordinate mouse_position();
};

#endif

/*
void Dot::handle_input(SDL_Event event)
{
    if(selected_ == true) {
        if(event.type == SDL_KEYDOWN) {
            switch( event.key.keysym.sym) {
                case SDLK_UP:
                    y_velocity_ -= kDotVelocity;
                    break;
                case SDLK_DOWN:
                    y_velocity_ += kDotVelocity;
                    break;
                case SDLK_LEFT:
                    x_velocity_ -= kDotVelocity;
                    break;
                case SDLK_RIGHT:
                    x_velocity_ += kDotVelocity;
                    break;
            }
        }
        else if(event.type == SDL_KEYUP) {
            switch( event.key.keysym.sym) {
                case SDLK_UP:
                    y_velocity_ += kDotVelocity;
                    break;
                case SDLK_DOWN:
                    y_velocity_ -= kDotVelocity;
                    break;
                case SDLK_LEFT:
                    x_velocity_ += kDotVelocity;
                    break;
                case SDLK_RIGHT:
                    x_velocity_ -= kDotVelocity;
                    break;
            }
        }
    }
}
*/
