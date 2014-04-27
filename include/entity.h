#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"

const int kEntityWidth  = 40;
const int kEntityHeight = 40;

const double kEntityVelocity     = 100;
const double kEntityAcceleration = 800;
const double kEntityRotationVelocity = 1000;

class Game;

class Entity : public GameObject
{
    private:

    public:
        // constructors/destructors
        Entity(Game * game);
        Entity(Game * game, double x, double y, double rot);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);

        void update(int deltaTicks);
        void stop();

        bool stopped();

        // accessors
};

#endif
