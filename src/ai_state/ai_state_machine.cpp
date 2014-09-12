#include "ai_state/ai_state_machine.h"
#include "ai_state/ai_state.h"
#include "ai_state/attack_state.h"
#include "ai_state/idle_state.h"
#include "ai_state/move_state.h"
#include "ai_state/rotate_state.h"
#include "ai_state/seek_state.h"
#include "point.h"

AIStateMachine::AIStateMachine(Entity * entity)
{
    entity_ = entity;
    next_state_ = nullptr;
    global_state_ = nullptr;

    attack_state_ = new AttackState();
    idle_state_ = new IdleState(entity);
    move_state_ = new MoveState(entity);
    rotate_state_ = new RotateState(entity);
    seek_state_ = new SeekState();

    current_state_ = idle_state_;
    previous_state_ = idle_state_;

}

AIStateMachine::~AIStateMachine()
{
    delete attack_state_;
    delete idle_state_;
    delete move_state_;
    delete rotate_state_;
    delete seek_state_;

}

bool AIStateMachine::update(int delta_ticks)
{
    bool keep_action = current_state_->update(entity_, delta_ticks);

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
    return idle_state_->action_type();
}
