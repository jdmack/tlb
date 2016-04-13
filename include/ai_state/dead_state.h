#ifndef TLB_AI_STATE_DEAD_STATE_H_
#define TLB_AI_STATE_DEAD_STATE_H_

#include "aiState/aiState.h"
#include "action/action.h"

class Entity;
class AIStateMachine;

class DeadState : public AIState
{
    private:

    public:
        DeadState(AIStateMachine * stateMachine, Entity * entity);
        ~DeadState();

        // accessors


        // mutators

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
