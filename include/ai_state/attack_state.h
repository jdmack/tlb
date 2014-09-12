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

    public:
        AttackState(AIStateMachine * state_machine, Entity * entity);
        ~AttackState();

        // accessors

        // mutators
        void set_target(Entity * target) { target_ = target; }

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
