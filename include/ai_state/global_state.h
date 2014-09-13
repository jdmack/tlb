#ifndef TLB_AI_STATE_GLOBAL_STATE_H_
#define TLB_AI_STATE_GLOBAL_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;
class AIStateMachine;

class GlobalState : public AIState
{
    private:

    public:
        GlobalState(AIStateMachine * state_machine, Entity * entity);
        ~GlobalState();

        // accessors

        // mutators

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
