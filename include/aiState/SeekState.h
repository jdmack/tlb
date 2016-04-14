#ifndef TLB_AI_STATE_SEEK_STATE_H_
#define TLB_AI_STATE_SEEK_STATE_H_

#include "aiState/AIState.h"
#include "action/Action.h"
#include "Point.h"

class Entity;
class AIStateMachine;
class MoveAction;

class SeekState : public AIState
{
    private:
        Entity * target_;
        MoveAction * moveAction_;
        Point targetLastPosition_;

    public:
        SeekState(AIStateMachine * stateMachine, Entity * entity);
        ~SeekState();

        // accessors


        // mutators
        void setTarget(Entity * target) { target_ = target; }

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();
};

#endif
