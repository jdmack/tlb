#include "ai_state/idle_state.h"
#include "ai_state/seek_state.h"
#include "ai_state/ai_state.h"
#include "ai_state/ai_state_machine.h"
#include "action/action.h"
#include "entity.h"
#include "game.h"
#include "entity_manager.h"
#include "util/logger.h"

IdleState::IdleState(AIStateMachine * state_machine, Entity * entity)
{
    state_machine_ = state_machine;
    entity_ = entity;
}

IdleState::~IdleState()
{

}

bool IdleState::update(int delta_ticks)
{
    return true;
}

void IdleState::stop()
{

}

void IdleState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: DEAD");
    stop_ = false;
}

void IdleState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: DEAD");
}

ActionType IdleState::action_type()
{
    return ACTION_DEAD;
}
