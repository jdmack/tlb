#ifndef TLB_AI_STATE_GLOBAL_STATE_H_
#define TLB_AI_STATE_GLOBAL_STATE_H_

#include "aiState/aiState.h"
#include "action/action.h"

class Entity;
class AIStateMachine;

class GlobalState : public AIState
{
    private:

    public:
        GlobalState(AIStateMachine * stateMachine, Entity * entity);
        ~GlobalState();

        // accessors

        // mutators

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
