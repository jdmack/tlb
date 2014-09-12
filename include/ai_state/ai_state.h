#ifndef TLB_AI_STATE_AI_STATE_H_
#define TLB_AI_STATE_AI_STATE_H_

#include "action/action.h"

enum AIStateType {
    STATE_ATTACK,
    STATE_IDLE,
    STATE_MOVE,
    STATE_ROTATE,
    STATE_SEEK,
    STATE_DEAD

};

class Entity;
class AIStateMachine;

class AIState
{
    protected:
        AIStateType type_;
        Entity * entity_;
        AIStateMachine * state_machine_;

    public:
        AIState();
        virtual ~AIState();

        // accessors
        AIStateType type() { return type_; }

        virtual bool update(int delta_ticks);
        virtual void stop();
        virtual void start();
        virtual void end();
        virtual ActionType action_type();

};

#endif
