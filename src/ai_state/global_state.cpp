#include "ai_state/global_state.h"
#include "ai_state/ai_state.h"
#include "ai_state/ai_state_machine.h"
#include "util/logger.h"
#include "entity.h"
#include "action/action.h"

GlobalState::GlobalState(AIStateMachine * state_machine, Entity * entity)
{
    type_ = STATE_GLOBAL;
    state_machine_ = state_machine;
    entity_ = entity;
}

GlobalState::~GlobalState()
{

}

bool GlobalState::update(int delta_ticks)
{
    // Check if dead
    if(state_machine_->current_state()->type() != STATE_DEAD) {
        if(entity_->hp()->empty()) {
            entity_->set_dead(true);
            state_machine_->set_next_state(STATE_DEAD);
        }
    }
    return true;
}

void GlobalState::stop()
{

}

void GlobalState::start()
{
}

void GlobalState::end()
{
}

ActionType GlobalState::action_type()
{
    return ACTION_IDLE;
}
