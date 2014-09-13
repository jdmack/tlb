#include "ai_state/ai_state_machine.h"
#include "ai_state/ai_state.h"
#include "ai_state/attack_state.h"
#include "ai_state/dead_state.h"
#include "ai_state/idle_state.h"
#include "ai_state/move_state.h"
#include "ai_state/rotate_state.h"
#include "ai_state/seek_state.h"
#include "ai_state/global_state.h"
#include "point.h"

AIStateMachine::AIStateMachine(Entity * entity)
{
    entity_ = entity;
    current_state_ = nullptr;;
    previous_state_ = nullptr;;
    next_state_ = nullptr;

    global_state_ = new GlobalState(this, entity);

    attack_state_ = new AttackState(this, entity);
    dead_state_ = new DeadState(this, entity);
    idle_state_ = new IdleState(this, entity);
    move_state_ = new MoveState(this, entity);
    rotate_state_ = new RotateState(this, entity);
    seek_state_ = new SeekState(this, entity);
}

AIStateMachine::~AIStateMachine()
{
    delete attack_state_;
    delete dead_state_;
    delete idle_state_;
    delete move_state_;
    delete rotate_state_;
    delete seek_state_;

}

bool AIStateMachine::update(int delta_ticks)
{
    // Start up the state machine if needed
    if(current_state_ == nullptr) {
        current_state_ = idle_state_;
        current_state_->start();
    }

    // Run global checks
    global_state_->update(delta_ticks);

    // Check if dead
    if((next_state_ != nullptr) && (next_state_->type() == STATE_DEAD)) {
        current_state_->end();
        current_state_ = next_state_;
        current_state_->start();
        next_state_ = nullptr;
    }

    bool keep_action = current_state_->update(delta_ticks);

    // TODO(2014-09-09/JM): Eventually make it so that when a state finishes, it responds with how many delta_ticks need to be run
    // in the next state and update() the new state with the remaining ticks

    if(!keep_action) {
        current_state_->end();

        if(next_state_ == nullptr) {
            current_state_ = static_cast<AIState *>(idle_state_);
        }
        else {
            current_state_ = next_state_;
            next_state_ = nullptr;
        }

        current_state_->start();
    }

    return true;
}

void AIStateMachine::stop()
{
    if(current_state_ != nullptr) {
        current_state_->stop();
    }
}

void AIStateMachine::move_command(Point destination)
{
    current_state_->stop();
    next_state_ = move_state_;
    move_state_->set_destination(destination);
}

void AIStateMachine::attack_command(Entity * target)
{
}

void AIStateMachine::rotate_command(Point position)
{
    current_state_->stop();
    next_state_ = rotate_state_;
    rotate_state_->set_position(position);
}



ActionType AIStateMachine::action_type()
{
    if(current_state_ != nullptr) {
        return current_state_->action_type();
    }
    return ACTION_IDLE;
}

void AIStateMachine::set_next_state(AIStateType type)
{
    switch(type) {
        case STATE_ATTACK:
            next_state_ = attack_state_;
            break;

        case STATE_DEAD:
            next_state_ = dead_state_;
            break;

        case STATE_IDLE:
            next_state_ = idle_state_;
            break;

        case STATE_MOVE:
            next_state_ = move_state_;
            break;

        case STATE_ROTATE:
            next_state_ = rotate_state_;
            break;

        case STATE_SEEK:
            next_state_ = seek_state_;
            break;
    }
}
