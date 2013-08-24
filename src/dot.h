#include "SDL/SDL.h"

#ifndef TLB_DOT_H_
#define TLB_DOT_H

const int kDotWidth    = 30;
const int kDotHeight   = 30;
const int kDotVelocity = 200;

class Dot
{
    private:
        float x_position_, y_position_;
        float x_velocity_, y_velocity_;
        SDL_Surface * surface_;

    public:
        Dot();
        void handle_input(SDL_Event event);
        void move(int deltaTicks);
        void show();
};

#endif
