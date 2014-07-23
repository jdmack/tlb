#include <cmath>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

#include "actions/zombie_action.h"

#include "game_object.h"
#include "point.h"
#include "utils/logger.h"
#include "entity.h"

ZombieAction::ZombieAction()
{
}


std::string ZombieAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}


bool ZombieAction::update(Entity * entity, int delta_ticks)
{

}
