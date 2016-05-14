#ifndef TLB_DOT_H_
#define TLB_DOT_H_

#include "GameObject.h"
#include "HitPoint.h"
#include "Point.h"
#include "action/Action.h"

const int kEntityWidth  = 40;
const int kEntityHeight = 40;

const double kEntityDefaultVelocity     = 5;
const double kEntityDefaultAcceleration = 800;
const double kEntityRotationVelocity = 1000;

const double kZombieAggroRadius = 144;
const double kZombieLeashRadius = 193;
const double kZombieAttackDamage = 1;
const double kZombieAttackRange = 70;
const double kZombieAttackCooldown = 3000;
const double kZombieAttackDuration = 500;

const double kPlayerAttackDamage = 2;
const double kPlayerAttackRange = 200;
const double kPlayerAttackCooldown = 3000;
const double kPlayerAttackDuration = 500;

enum EntityType {
    PLAYER,
    ZOMBIE,
    HUMAN
};

//class Action;
class AIStateMachine;

class Entity : public GameObject
{
    private:
        HitPoint * hp_;
        bool controllable_;
        EntityType type_;
        double maximumSpeed_;
        bool dead_;
        //Action * currentAction_;
        AIStateMachine * stateMachine_;

    public:
        // constructors/destructors
        Entity(EntityType type);
        Entity(EntityType type, Point position, double rot);

        // overridden
        //void select();
        //void deselect();
        bool containsPoint(double x, double y);
        void move(Point point);
        void rotate(Point point);
        void attack(Entity * target);

        void takeDamage(int damage, Entity * attacker);

        void update(int deltaTicks);
        void stop();

        bool stopped();

        // accessors
        HitPoint * hp() const { return hp_; }
        bool controllable() const { return controllable_; }
        double maximumSpeed() const { return maximumSpeed_; }
        EntityType type() const { return type_; }
        bool dead() const { return dead_; }

        // mutators
        void setControllable(bool controllable) { controllable_ = controllable; }
        void setMaximumSpeed(double maximumSpeed) { maximumSpeed_ = maximumSpeed; }
        void setType(EntityType type) { type_ = type; }
        void setDead(bool dead);

        bool isEntity() const { return true; }
        ActionType actionType();

};

#endif
