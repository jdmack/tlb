#ifndef TLB_AI_STATE_SEEK_STATE_H_
#define TLB_AI_STATE_SEEK_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"
#include "point.h"

class Entity;
class AIStateMachine;
class MoveAction;

class SeekState : public AIState
{
    private:
        Entity * target_;
        MoveAction * move_action_;
        Point target_last_position_;

    public:
        SeekState(AIStateMachine * state_machine, Entity * entity);
        ~SeekState();

        // accessors


        // mutators
        void set_target(Entity * target) { target_ = target; }

        bool update(int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();
};

#endif
