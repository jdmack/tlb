#include "action/Action.h"
#include "Entity.h"

Action::Action()
{
    type_ = ACTION_IDLE;
}

Action::~Action()
{

}

bool Action::update(Entity * entity, int deltaTicks)
{
    return true;
}

void Action::stop()
{

}
