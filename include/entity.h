#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "game_object.h"
#include "hit_point.h"
#include "point.h"
#include "action/action.h"

const int kEntityWidth  = 40;
const int kEntityHeight = 40;

const double kEntityDefaultVelocity     = 100;
const double kEntityDefaultAcceleration = 800;
const double kEntityRotationVelocity = 1000;

enum EntityType {
    PLAYER,
    ZOMBIE,
    HUMAN
};

class Game;
//class Action;
class AIStateMachine;

class Entity : public GameObject
{
    private:
        HitPoint * hp_;
        bool controllable_;
        EntityType type_;
        double maximum_speed_;
        bool dead_;
        //Action * current_action_;
        AIStateMachine * state_machine_;

    public:
        // constructors/destructors
        Entity(Game * game, EntityType type);
        Entity(Game * game, EntityType type, Point position, double rot);

        // overridden
        //void select();
        //void deselect();
        bool contains_point(double x, double y);
        void move(Point point);
        void rotate(Point point);
        void attack(Entity * target);

        void update(int deltaTicks);
        void stop();

        bool stopped();

        // accessors
        HitPoint * hp() const { return hp_; }
        bool controllable() const { return controllable_; }
        double maximum_speed() const { return maximum_speed_; }
        EntityType type() const { return type_; }
        bool dead() const { return dead_; }
        Action * current_action() const { return current_action_; }

        // mutators
        void set_controllable(bool controllable) { controllable_ = controllable; }
        void set_maximum_speed(double maximum_speed) { maximum_speed_ = maximum_speed; }
        void set_type(EntityType type) { type_ = type; }
        void set_dead(bool dead) { dead_ = dead; }
        void set_current_action(Action * action) { current_action_ = action; }

        bool is_entity() const { return true; }
        ActionType action_type();

};

#endif
