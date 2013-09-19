#include <cmath>
#include <vector>

#include "movement_action.h"

#include "game_object.h"
#include "grid.h"
#include "level.h"
#include "movement.h"
#include "point.h"
#include "pathfinder.h"
#include "utils/logger.h"

MovementAction::MovementAction(Point start, Point end, Level * level)
{
	start_ = start;
	end_ = end;
	level_ = level;

	path_ = new std::vector<Movement *>();
}

void MovementAction::find_path()
{
	Pathfinder pathfinder(level_);

	// Get path as list of nodes
	std::list<GridNode *> * nodes;
	nodes = pathfinder.run(level_->grid()->node_at_point(start_), level_->grid()->node_at_point(end_));

	// Convert node path into Movement path



}
