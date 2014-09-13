#include "ai_state/seek_state.h"
#include "ai_state/idle_state.h"
#include "ai_state/attack_state.h"
#include "ai_state/ai_state_machine.h"
#include "util/logger.h"
#include "entity.h"
#include "action/move_action.h"
#include "game.h"

SeekState::SeekState(AIStateMachine * state_machine, Entity * entity)
{
    type_ = STATE_SEEK;
    state_machine_ = state_machine;
    entity_ = entity;
    move_action_ = nullptr;
    target_ = nullptr;
}

SeekState::~SeekState()
{

}

bool SeekState::update(int delta_ticks)
{
    // Only do state transition checks if next_state hasn't been chosen yet
    if(state_machine_->next_state() == nullptr) {

        if(target_ == nullptr) {
            // switch to IDLE
            state_machine_->set_next_state(STATE_IDLE);
            return false;
        }

        Point position = entity_->position();

        // check if target has exceeded leash range
        if(position.distance_from(Point(target_->x_position(), target_->y_position())) >= kZombieLeashRadius) {
            move_action_->stop();
            state_machine_->set_next_state(STATE_IDLE);

            Logger::write("SEEK: Out of leash range");
        }

        // check if target has moved far from we think it is
        // TODO(2014-08-15/JM): Hard coded number 12 here for distance, change
        else if(target_last_position_.distance_from(target_->position()) >= 12) {
            move_action_->stop();
            state_machine_->set_next_state(STATE_SEEK);
            Logger::write("SEEK: Recalculating movement to target");
        }
    }

    // Perform movement

    bool keep_action = move_action_->update(entity_, delta_ticks);

    if(!keep_action) {
        if(state_machine_->next_state() == nullptr) {
            state_machine_->attack_state()->set_target(target_);
            state_machine_->set_next_state(STATE_ATTACK);
        }
    }

    return keep_action;
}

void SeekState::stop()
{
    if(move_action_ != nullptr) {
        move_action_->stop();
    }
}

void SeekState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: SEEK");

    move_action_ = new MoveAction(entity_->position(), target_->position(), Game::instance()->level());
    move_action_->remove_movements_back();
    target_last_position_ = Point(target_->x_position(), target_->y_position());

}

void SeekState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: SEEK");
    delete move_action_;
    move_action_ = nullptr;
}

ActionType SeekState::action_type()
{
    return ACTION_MOVE;
}
