#include "ai_state/idle_state.h"
#include "ai_state/ai_state.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{

}

bool IdleState::update(Entity * entity, int delta_ticks)
{

    return true;
}

void IdleState::stop()
{

}
