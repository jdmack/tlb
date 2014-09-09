#ifndef TLB_AI_STATE_ATTACK_STATE_H_
#define TLB_AI_STATE_ATTACK_STATE_H_

#include "ai_state/ai_state.h"

class Entity;

class AttackState : public AIState
{
    protected:

    public:
        AttackState();
        ~AttackState();

        // accessors
        //ActionType type();

        bool update(Entity * entity, int delta_ticks);
        void stop();

};

#endif
