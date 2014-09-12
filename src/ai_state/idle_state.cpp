#include "ai_state/idle_state.h"
#include "ai_state/ai_state.h"
#include "action/action.h"

IdleState::IdleState(Entity * entity)
{
    entity_ = entity;
    stop_ = false;
}

IdleState::~IdleState()
{

}

bool IdleState::update(Entity * entity, int delta_ticks)
{
    return !stop_;
}

void IdleState::stop()
{
    stop_ = true;
}

ActionType IdleState::action_type()
{
    return ACTION_IDLE;
}
