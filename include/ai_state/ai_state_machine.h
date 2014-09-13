#ifndef TLB_AI_STATE_AI_STATE_MACHINE_H_
#define TLB_AI_STATE_AI_STATE_MACHINE_H_

#include "action/action.h"
#include "point.h"
#include "ai_state/ai_state.h"

class Entity;
class AIState;
class AttackState;
class DeadState;
class IdleState;
class MoveState;
class RotateState;
class SeekState;
class GlobalState;

class AIStateMachine
{
    private:
        Entity * entity_;
        AIState * current_state_;
        AIState * previous_state_;
        AIState * next_state_;
        GlobalState * global_state_;

        AttackState * attack_state_;
        DeadState * dead_state_;
        IdleState * idle_state_;
        MoveState * move_state_;
        RotateState * rotate_state_;
        SeekState * seek_state_;

    public:
        AIStateMachine(Entity * entity);
        ~AIStateMachine();

        // accessors
        Entity * entity() { return entity_; }
        AIState * current_state() { return current_state_; }
        AIState * previous_state() { return previous_state_; }
        AIState * next_state() { return next_state_; }
        GlobalState * global_state() { return global_state_; }
        AttackState * attack_state() { return attack_state_; }
        DeadState * dead_state() { return dead_state_; }
        IdleState * idle_state() { return idle_state_; }
        MoveState * move_state() { return move_state_; }
        RotateState * rotate_state() { return rotate_state_; }
        SeekState * seek_state() { return seek_state_; }

        // mutators
        void set_entity(Entity * entity) { entity_ = entity; }
        void set_current_state(AIState * current_state) { current_state_ = current_state; }
        void set_previous_state(AIState * previous_state) { previous_state_ = previous_state; }
        void set_next_state(AIState * next_state) { next_state_ = next_state; }
        void set_global_state(GlobalState * global_state) { global_state_ = global_state; }

        void set_next_state(AIStateType type);

        void move_command(Point destination);
        void attack_command(Entity * target);
        void rotate_command(Point position);

        bool update(int delta_ticks);
        void stop();
        ActionType action_type();

};

#endif
