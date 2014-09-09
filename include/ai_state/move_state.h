#ifndef TLB_AI_STATE_MOVE_STATE_H_
#define TLB_AI_STATE_MOVE_STATE_H_

#include "ai_state/ai_state.h"

class Entity;

class MoveState : public AIState
{
    protected:

    public:
        MoveState();
        ~MoveState();

        // accessors
        //ActionType type();

        bool update(Entity * entity, int delta_ticks);
        void stop();

};

#endif
