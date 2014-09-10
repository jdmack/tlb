#ifndef TLB_AI_STATE_ROTATE_STATE_H_
#define TLB_AI_STATE_ROTATE_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"

class Entity;

class RotateState : public AIState
{
    protected:

    public:
        RotateState();
        ~RotateState();

        // accessors
        //ActionType type();

        bool update(Entity * entity, int delta_ticks);
        void stop();
        ActionType action_type() { return ACTION_ROTATE; }

};

#endif
