#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"

const int kDotWidth    = 30;
const int kDotHeight   = 30;
const int kDotVelocity = 200;

class Dot : public GameObject
{
    private:
        double x_velocity_;
        double y_velocity_;

    public:
        // constructors/destructors
        Dot();
        Dot(double x, double y, double rot);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);

        void handle_input(SDL_Event event);
        void update(int deltaTicks);
};

#endif
