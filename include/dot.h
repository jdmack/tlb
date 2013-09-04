#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"

const int kDotWidth  = 50;
const int kDotHeight = 50;

const double kDotVelocity     = 200;
const double kDotAcceleration = 400;
//const double kDotRotationVelocity = 3.141592653589793;
const double kDotRotationVelocity = 180;

class Dot : public GameObject
{
    private:

    public:
        // constructors/destructors
        Dot();
        Dot(double x, double y, double rot);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);
        void stop();

        void update(int deltaTicks);

        // accessors
};

#endif
