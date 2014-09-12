#ifndef TLB_AI_STATE_ROTATE_STATE_H_
#define TLB_AI_STATE_ROTATE_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"
#include "point.h"

class Entity;
class RotateAction;
class AIStateMachine;

class RotateState : public AIState
{
    private:
        Point position_;
        RotateAction * rotate_action_;

    public:
        RotateState(AIStateMachine * state_machine, Entity * entity);
        ~RotateState();

        // accessors
        Point position() const { return position_; }

        // mutators
        void set_position(Point position) { position_ = position; }

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
