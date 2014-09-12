#ifndef TLB_AI_STATE_IDLE_STATE_H_
#define TLB_AI_STATE_IDLE_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;
class AIStateMachine;

class IdleState : public AIState
{
    private:
        bool stop_;

    public:
        IdleState(AIStateMachine * state_machine, Entity * entity);
        ~IdleState();

        // accessors


        // mutators

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
