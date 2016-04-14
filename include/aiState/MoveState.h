#ifndef TLB_AI_STATE_MOVE_STATE_H_
#define TLB_AI_STATE_MOVE_STATE_H_

#include "aiState/AIState.h"
#include "action/Action.h"
#include "Point.h"

class Entity;
class MoveAction;
class AIStateMachine;

class MoveState : public AIState
{
    private:
        Point destination_;
        MoveAction * moveAction_;

    public:
        MoveState(AIStateMachine * stateMachine, Entity * entity);
        ~MoveState();

        // accessors
        Point destination() const { return destination_; }

        // mutators
        void setDestination(Point destination) { destination_ = destination; }

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
