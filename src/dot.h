#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"

const int kDotWidth    = 30;
const int kDotHeight   = 30;
const int kDotVelocity = 200;

class Dot : public GameObject
{
    private:
        float x_velocity_;
        float y_velocity_;

    public:
        Dot(std::string art_asset);
        void handle_input(SDL_Event event);
        void move(int deltaTicks);
};

#endif
