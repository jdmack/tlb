#include <cmath>
#include <list>
#include <vector>

#include "movement_action.h"

#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
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

	find_path();
}

void MovementAction::find_path()
{
	Logger::write(Logger::string_stream << "Blah 1");
	Pathfinder pathfinder(level_);
	Logger::write(Logger::string_stream << "Blah 2");

	// Get path as list of nodes
	std::list<GridNode *> * nodes;
	nodes = pathfinder.run(level_->grid()->node_at_point(start_), level_->grid()->node_at_point(end_));
	Logger::write(Logger::string_stream << "Blah 3");

	// Convert node path into Movement path
	while(nodes->size() >= 2)
	{

	    // TODO(2013-09-20/JM): Add code to filter straight line paths into a single movement

	    GridNode * start_node = nodes->front();
	    nodes->pop_front();
	    GridNode * end_node = nodes->front();

        // Create movement vectore
        Vector vector = Vector(start_node->center_point().x(), start_node->center_point().y(), end_node->center_point().x(), end_node->center_point().y());

        // Create movement
        Movement * this_movement = new Movement(vector, end_node->center_point());

        path_->push_back(this_movement);
	}
	Logger::write(Logger::string_stream << "Blah 4");

	// Set current movement to beginning
	current_ = path_->begin();

	Logger::write(Logger::string_stream << "Path created: " << path_->size() << " movements");

    // Print path
    for(std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
            /* std::cout << *it; ... */
    }
}

bool MovementAction::next_movement()
{
    if(current_ == path_->end()) {
        return false;
    }
    else {
        current_++;
        return true;
    }
}

