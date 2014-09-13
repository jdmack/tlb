#ifndef TLB_AI_STATE_ATTACK_STATE_H_
#define TLB_AI_STATE_ATTACK_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;
class AIStateMachine;
class AttackAction;

class AttackState : public AIState
{
    private:
        Entity * target_;
        AttackAction * attack_action_;
        int damage_;
        double range_;

    public:
        AttackState(AIStateMachine * state_machine, Entity * entity);
        ~AttackState();

        // accessors
        int damage() const { return damage_; }
        double range() const { return range_; }

        // mutators
        void set_target(Entity * target) { target_ = target; }
        void set_damage(int damage) { damage_ = damage; }
        void set_range(double range) { range_ = range; }

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
