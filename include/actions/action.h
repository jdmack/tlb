#ifndef TLB_ACTION_H_
#define TLB_ACTION_H_

#include <string>

const std::string kActionMovement = "MovementAction";
const std::string kActionIdle    = "IdleAction";
const std::string kActionEmpty    = "EmptyAction";
const std::string kActionZombie   = "ZombieAction";

enum ActionType {
    ACTION_MOVEMENT,
    ACTION_IDLE,
    ACTION_ZOMBIE,
    ACTION_SEEK,
    ACTION_ATTACK
};

class Entity;

class Action
{
    protected:
        ActionType type_;

    public:
        Action();

        // accessors
        virtual ActionType type() { return type_; }

        virtual ~Action();
        virtual bool update(Entity * entity, int delta_ticks);

};

#endif
