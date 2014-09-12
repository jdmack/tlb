#ifndef TLB_AI_STATE_DEAD_STATE_H_
#define TLB_AI_STATE_DEAD_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;
class AIStateMachine;

class DeadState : public AIState
{
    private:

    public:
        DeadState(AIStateMachine * state_machine, Entity * entity);
        ~DeadState();

        // accessors


        // mutators

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
