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
#include "dot.h"

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
	Pathfinder pathfinder(level_);

	// Get path as list of nodes
	std::list<GridNode *> * nodes;
	nodes = pathfinder.run(level_->grid()->node_at_point(start_), level_->grid()->node_at_point(end_));

	Logger::string_stream << "Path: ";
	for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	}
	Logger::write(Logger::string_stream);

	// Convert node path into Movement path
	if(nodes->size() >= 2) {
        while(nodes->size() > 1)
        {
            // TODO(2013-09-20/JM): Add code to filter straight line paths into a single movement

            GridNode * start_node = nodes->front();
            nodes->pop_front();
            GridNode * end_node = nodes->front();

            // Create movement vectore
            Vector vector = Vector(start_node->center_point().x(), start_node->center_point().y(), end_node->center_point().x(), end_node->center_point().y());

            // Create movement
            Movement * this_movement = new Movement(vector, start_node->center_point(), end_node->center_point());

            this_movement->set_maximum_velocity(Vector(kDotVelocity, this_movement->vector().direction()));
            path_->push_back(this_movement);
        }
	}
	else {

	}

	// Set current movement to beginning
	current_ = path_->begin();

	Logger::write(Logger::string_stream << "Path created: " << path_->size() << " movements");

    // Print path
    //for(std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
    //        /* std::cout << *it; ... */
    //}
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

