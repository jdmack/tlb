#include "ai_state/attack_state.h"
#include "ai_state/rotate_state.h"
#include "ai_state/seek_state.h"
#include "ai_state/ai_state.h"
#include "ai_state/ai_state_machine.h"
#include "util/logger.h"
#include "entity.h"
#include "action/attack_action.h"
#include "action/rotate_action.h"

AttackState::AttackState(AIStateMachine * state_machine, Entity * entity)
{
    type_ = STATE_ATTACK;
    state_machine_ = state_machine;
    entity_ = entity;
    target_ = nullptr;
    attack_action_ = nullptr;
    command_ = false;
    damage_ = 0;
    range_ = 0;
}

AttackState::~AttackState()
{

}

bool AttackState::update(int delta_ticks)
{

    Point position = entity_->position();
    Point target_position = Point(target_->x_position(), target_->y_position());

    // Only do checks if the next state hasn't been determined yet
    if(state_machine_->next_state() == nullptr) {
        // Check if we are in range
        if(target_position.distance_from(position) > attack_action_->range()) {
            if(command_) {
                state_machine_->set_next_state(STATE_SEEK);
                state_machine_->seek_state()->set_target(target_);
            }
            else {
                state_machine_->set_next_state(STATE_IDLE);
            }
            Logger::write("ATTACK: Target out of attack range");
            return false;
        }

        // Check if we are facing the target
        if(!RotateAction::facing(entity_, target_, attack_action_->arc())) {
            // TODO(2014-09-12/JM): Need to implement a way for the renderer to tell which direction entity is
            // rotating if we end up with a rotation animation at some point
            if(command_) {
                state_machine_->set_next_state(STATE_ROTATE);
                state_machine_->rotate_state()->set_position(target_position);
            }
            else {
                state_machine_->set_next_state(STATE_IDLE);
            }
            Logger::write("ATTACK: Not facing target");
            return false;
        }
    }

    // Perform attack
    //if(next_state_ != BLANK) break;   // NOT SURE WHAT THIS WAS DOING

    bool keep_action = attack_action_->update(entity_, delta_ticks);

    if(!keep_action) {
        if(state_machine_->next_state() == nullptr) {
            state_machine_->set_next_state(STATE_IDLE);
        }
    }

    return keep_action;
}

void AttackState::stop()
{
    if(attack_action_ != nullptr) {
        attack_action_->stop();
    }
}

void AttackState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: ATTACK");
    //attack_action_->reset();
    attack_action_ = new AttackAction(target_);

    attack_action_->set_entity(entity_);
    attack_action_->set_damage(damage_);
    attack_action_->set_range(range_);
    // TODO(2014-09-12/JM): Set attack cooldown and duration



}

void AttackState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: ATTACK");
    delete attack_action_;
    attack_action_ = nullptr;
    command_ = false;
}

ActionType AttackState::action_type()
{
    if(attack_action_ != nullptr) {
        return attack_action_->type();
    }
    return ACTION_ATTACK;
}
