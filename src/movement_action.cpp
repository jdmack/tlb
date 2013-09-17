#include <cmath>
#include "movement_action.h"
#include "coordinate.h"
#include "game_object.h"
#include "pathfinder.h"
#include "utils/logger.h"

MovementAction::MovementAction()
{
	path_ = new std::vector<Movement *>();
}

MovementAction::MovementAction(std::vector<Movement *> path)
{
	path_ = path;
	current_ = path_.begin();
}
