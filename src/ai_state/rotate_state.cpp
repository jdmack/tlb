#include "ai_state/rotate_state.h"
#include "ai_state/ai_state.h"
#include "point.h"
#include "action/action.h"
#include "action/rotate_action.h"
#include "game.h"
#include "entity.h"

RotateState::RotateState(Entity * entity)
{
    entity_ = entity;
    position_ = Point(0, 0);
    rotate_action_ = nullptr;
}

RotateState::~RotateState()
{

}

bool RotateState::update(Entity * entity, int delta_ticks)
{
    bool keep_action = rotate_action_->update(entity, delta_ticks);

    return keep_action;
}

void RotateState::stop()
{
    if(rotate_action_ != nullptr) {
        rotate_action_->stop();
    }
}

void RotateState::start()
{
    // Create rotate action
    rotate_action_ = new RotateAction(entity_, position_);
}

void RotateState::end()
{
    // clear out old data
    position_ = Point(0, 0);
    delete rotate_action_;
    rotate_action_ = nullptr;
}

ActionType RotateState::action_type()
{
    return ACTION_ROTATE;
}
