#include "ai_state/move_state.h"
#include "ai_state/ai_state.h"
#include "point.h"
#include "action/action.h"
#include "action/move_action.h"
#include "game.h"
#include "entity.h"

MoveState::MoveState(Entity * entity)
{
    entity_ = entity;
    destination_ = Point(0, 0);
    move_action_ = nullptr;
}

MoveState::~MoveState()
{

}

bool MoveState::update(Entity * entity, int delta_ticks)
{
    bool keep_action = move_action_->update(entity, delta_ticks);

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
    // Create movement action
    move_action_ = new MoveAction(entity_->position(), destination_, Game::instance()->level());
    if(move_action_->empty_path()) {
        //Logger::write("Empty path, cancelling Move");
        return;
    }

}

void MoveState::end()
{
    // clear out old data
    destination_ = Point(0, 0);
    delete move_action_;
    move_action_ = nullptr;
}

ActionType MoveState::action_type()
{
    return ACTION_MOVE;
}
