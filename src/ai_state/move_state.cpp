#include "ai_state/move_state.h"
#include "ai_state/ai_state.h"
#include "point.h"
#include "action/action.h"
#include "action/move_action.h"

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
    return true;
}

void MoveState::stop()
{

}

void MoveState::start()
{
    // clear out old data
    destination_ = Point(0, 0);

}

void MoveState::end()
{

}

ActionType MoveState::action_type()
{
    return ACTION_MOVE;
}
