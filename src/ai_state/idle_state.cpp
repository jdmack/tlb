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
    stop_ = false;
}

IdleState::~IdleState()
{

}

bool IdleState::update(int delta_ticks)
{
    Point position = entity_->position();
    std::vector<Entity *> entities;

    if(entity_->type() == PLAYER) {
        return !stop_;
    }
    else {
        // ZOMBIE
        // Check for entities within Aggro Range
        entities = Game::instance()->entity_manager()->get_entities_near(position, kZombieAggroRadius);
        Entity * target = nullptr;

        //TODO(2014-07-24/JM): Choose way of selecting target if there are multiple
        while(target == nullptr) {
            if(entities.empty()) {
                //Logger::write(Logger::ss << "Found nothing nearby");
                return true;
            }
            if(entities.back()->object_id() == entity_->object_id()) {
                entities.pop_back();
                continue;
            }
            if(entities.back()->type() == ZOMBIE) {
                entities.pop_back();
                continue;
            }


            // Found a target, setup next action
            target = entities.back();
            entities.pop_back();
        }

        if(target != nullptr) {
            // Found target, decide next action
            state_machine_->seek_state()->set_target(target);
            state_machine_->set_next_state(STATE_SEEK);
            return false;
        }

        return true;
    }
}

void IdleState::stop()
{
    stop_ = true;
}

void IdleState::start()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Entering State: IDLE");
    stop_ = false;
}

void IdleState::end()
{
    Logger::write(Logger::ss << "Entity: " << entity_->object_id() << " - Exiting  State: IDLE");
}

ActionType IdleState::action_type()
{
    return ACTION_IDLE;
}
