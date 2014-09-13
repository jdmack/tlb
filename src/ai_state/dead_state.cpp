#include "ai_state/dead_state.h"
#include "ai_state/ai_state.h"
#include "ai_state/ai_state_machine.h"
#include "action/action.h"
#include "entity.h"
#include "util/logger.h"

DeadState::DeadState(AIStateMachine * state_machine, Entity * entity)
{
    type_ = STATE_DEAD;
    state_machine_ = state_machine;
    entity_ = entity;
}

DeadState::~DeadState()
{

}

bool DeadState::update(int delta_ticks)
{
    return true;
}

void DeadState::stop()
{

}

void DeadState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: DEAD");
}

void DeadState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: DEAD");
}

ActionType DeadState::action_type()
{
    return ACTION_DEAD;
}
