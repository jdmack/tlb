#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"
#include "hit_point.h"

const int kEntityWidth  = 40;
const int kEntityHeight = 40;

const double kEntityVelocity     = 100;
const double kEntityAcceleration = 800;
const double kEntityRotationVelocity = 1000;

class Game;

class Entity : public GameObject
{
    private:
        HitPoint * hp_;
        bool controllable_;

    public:
        // constructors/destructors
        Entity(Game * game);
        Entity(Game * game, Point position, double rot);

        // overridden
        void select();
        void deselect();
        bool contains_point(double x, double y);
        void move(double x, double y);

        void update(int deltaTicks);
        void stop();

        bool stopped();

        // accessors
        HitPoint * hp() const { return hp_; }
        bool controllable() const { return controllable_; }

        // mutators
        void set_controllable(bool controllable) { controllable_ = controllable; }
};

#endif
