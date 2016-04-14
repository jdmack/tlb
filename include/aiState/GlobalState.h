#ifndef TLB_AI_STATE_GLOBAL_STATE_H_
#define TLB_AI_STATE_GLOBAL_STATE_H_

#include "aiState/AIState.h"
#include "action/Action.h"

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
