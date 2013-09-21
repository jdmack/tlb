#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"

const int kDotWidth  = 40;
const int kDotHeight = 40;

const double kDotVelocity     = 100;
const double kDotAcceleration = 800;
const double kDotRotationVelocity = 600;

class Game;

class Dot : public GameObject
{
    private:

    public:
        // constructors/destructors
        Dot(Game * game);
        Dot(Game * game, double x, double y, double rot);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);

        void update(int deltaTicks);

        // accessors
};

#endif
