#ifndef TLB_AI_STATE_ATTACK_STATE_H_
#define TLB_AI_STATE_ATTACK_STATE_H_

#include "aiState/aiState.h"
#include "action/action.h"

class Entity;
class AIStateMachine;
class AttackAction;

class AttackState : public AIState
{
    private:
        Entity * target_;
        AttackAction * attackAction_;
        int damage_;
        double range_;
        bool command_;

    public:
        AttackState(AIStateMachine * stateMachine, Entity * entity);
        ~AttackState();

        // accessors
        int damage() const { return damage_; }
        double range() const { return range_; }
        bool command() const { return command_; }

        // mutators
        void setTarget(Entity * target) { target_ = target; }
        void setDamage(int damage) { damage_ = damage; }
        void setRange(double range) { range_ = range; }
        void setCommand(bool command) { command_ = command; }

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
