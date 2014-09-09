#ifndef TLB_AI_STATE_IDLE_STATE_H_
#define TLB_AI_STATE_IDLE_STATE_H_

#include "ai_state/ai_state.h"

class Entity;

class IdleState : public AIState
{
    protected:

    public:
        IdleState();
        ~IdleState();

        // accessors
        //ActionType type();

        bool update(Entity * entity, int delta_ticks);
        void stop();

};

#endif
