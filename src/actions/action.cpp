#include "actions/action.h"

Action::Action()
{
    type_ = kActionEmpty;
}

Action::~Action()
{

}

bool Action::update(Entity * entity, int delta_ticks)
{
    return true;
}
