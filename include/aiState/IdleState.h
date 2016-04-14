#ifndef TLB_AI_STATE_IDLE_STATE_H_
#define TLB_AI_STATE_IDLE_STATE_H_

#include "aiState/AIState.h"
#include "action/Action.h"

class Entity;
class AIStateMachine;

class IdleState : public AIState
{
    private:
        bool stop_;

    public:
        IdleState(AIStateMachine * stateMachine, Entity * entity);
        ~IdleState();

        // accessors


        // mutators

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
