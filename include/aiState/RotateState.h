#ifndef TLB_AI_STATE_ROTATE_STATE_H_
#define TLB_AI_STATE_ROTATE_STATE_H_

#include "aiState/AIState.h"
#include "action/Action.h"
#include "Point.h"

class Entity;
class RotateAction;
class AIStateMachine;

class RotateState : public AIState
{
    private:
        Point position_;
        RotateAction * rotateAction_;

    public:
        RotateState(AIStateMachine * stateMachine, Entity * entity);
        ~RotateState();

        // accessors
        Point position() const { return position_; }

        // mutators
        void setPosition(Point position) { position_ = position; }

        bool update(int deltaTicks);
        void stop();
        void start();
        void end();
        ActionType actionType();

};

#endif
