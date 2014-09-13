#include "ai_state/move_state.h"
#include "ai_state/ai_state.h"
#include "ai_state/ai_state_machine.h"
#include "point.h"
#include "action/action.h"
#include "action/move_action.h"
#include "game.h"
#include "entity.h"
#include "util/logger.h"

MoveState::MoveState(AIStateMachine * state_machine, Entity * entity)
{
    type_ = STATE_MOVE;
    state_machine_ = state_machine;
    entity_ = entity;
    destination_ = Point(0, 0);
    move_action_ = nullptr;
}

MoveState::~MoveState()
{

}

bool MoveState::update(int delta_ticks)
{
    bool keep_action = move_action_->update(entity_, delta_ticks);
    if(!keep_action) {
        state_machine_->set_previous_state(nullptr);
    }

    return keep_action;
}

void MoveState::stop()
{
    if(move_action_ != nullptr) {
        move_action_->stop();
    }
}

void MoveState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: MOVE");
    // Create move action
    move_action_ = new MoveAction(entity_->position(), destination_, Game::instance()->level());
    if(move_action_->empty_path()) {
        //Logger::write("Empty path, cancelling Move");
        return;
    }

}

void MoveState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: MOVE");
    // clear out old data
    delete move_action_;
    move_action_ = nullptr;
}

ActionType MoveState::action_type()
{
    return ACTION_MOVE;
}
