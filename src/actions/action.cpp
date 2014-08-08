#include "actions/action.h"

Action::Action()
{
    type_ = ACTION_IDLE;
}

Action::~Action()
{

}

bool Action::update(Entity * entity, int delta_ticks)
{
    return true;
}

void Action::stop()
{

}
