#ifndef TLB_AI_STATE_MOVE_STATE_H_
#define TLB_AI_STATE_MOVE_STATE_H_

#include "ai_state/ai_state.h"
#include "action/action.h"
#include "point.h"

class Entity;
class MoveAction;

class MoveState : public AIState
{
    private:
        Point destination_;
        Entity * entity_;
        MoveAction * move_action_;


    public:
        MoveState(Entity * entity);
        ~MoveState();

        // accessors
        Point destination() const { return destination_; }

        // mutators
        void set_destination(Point destination) { destination_ = destination; }

        bool update(Entity * entity, int delta_ticks);
        void stop();
        void start();
        void end();
        ActionType action_type();

};

#endif
