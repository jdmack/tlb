#ifndef TLB_AI_STATE_SEEK_STATE_H_
#define TLB_AI_STATE_SEEK_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;

class SeekState : public AIState
{
    protected:

    public:
        SeekState();
        ~SeekState();

        // accessors
        //ActionType type();

        bool update(Entity * entity, int delta_ticks);
        void stop();
        ActionType action_type() { return ACTION_MOVE; }
};

#endif
