#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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
    bool use_pathfinding = true;

	start_ = start;
	end_ = end;
	level_ = level;

	type_ = kActionMovement;

	path_ = new std::vector<Movement *>();

	if(use_pathfinding) {
	    find_path();
	}
	else {
        // Create movement vectore
        Vector vector = Vector(start, end);

        // Create movement
        Movement * this_movement = new Movement(vector, start, end);
        this_movement->set_maximum_velocity(Vector(kDotVelocity, this_movement->vector().direction()));
        path_->push_back(this_movement);
        current_ = path_->begin();
	}
}

void MovementAction::find_path()
{
    // Create Pathfinder
	Pathfinder pathfinder(level_);

	// Get path as list of nodes
	std::list<GridNode *> * nodes;
	nodes = pathfinder.run(level_->grid()->node_at_point(start_), level_->grid()->node_at_point(end_));

    // Print the path to log
	Logger::string_stream << "Path: ";
	for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	    //Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	    Logger::string_stream << (*iterator)->to_string() << " ";
	}
	Logger::write(Logger::string_stream);
    Logger::write(Logger::string_stream << "# of nodes: " << nodes->size());

	// Convert node path into Movement path
    while(nodes->size() > 1) {
	    if(nodes->size() >= 2) {
            // TODO(2013-09-20/JM): Add code to filter straight line paths into a single movement

            GridNode * start_node = nodes->front();
            if(nodes->empty()) {
                Logger::write(Logger::string_stream << "Uh oh, list is empty dude!\n");
                break;
            }
            nodes->pop_front();
            if(nodes->empty()) {
                Logger::write(Logger::string_stream << "Uh oh, list is empty dude!\n");
                break;
            }
            GridNode * end_node = nodes->front();

            // Create movement vector
            Vector vector = Vector(start_node->center_point(), end_node->center_point());

            // Create movement
            Logger::write(Logger::string_stream << "Start Point: " << start_node->center_point().to_string());
            Logger::write(Logger::string_stream << "End Point: " << end_node->center_point().to_string());
            Movement * this_movement = new Movement(vector, start_node->center_point(), end_node->center_point());

            this_movement->set_maximum_velocity(Vector(kDotVelocity, this_movement->vector().direction()));
            path_->push_back(this_movement);
        }
	    else {
            // shouldn't ever run this
            break;
	    }
	}

	// Set current movement to beginning
	current_ = path_->begin();
	if(!path_->empty()) {
	    Logger::write(Logger::string_stream << "MovementAction::first_movement(): " << (*current_)->to_string());
	}
	Logger::write(Logger::string_stream << "Path created: " << path_->size() << " movements");

	// reset grid
	level_->grid()->reset_pathfinding();
}

bool MovementAction::next_movement()
{
    current_++;
    if(current_ == path_->end()) {
        Logger::write(Logger::string_stream << "MovementAction::next_movement(): No more Movements");
        return false;
    }
    else {
        //current_++;
        Logger::write(Logger::string_stream << "MovementAction::next_movement(): " << (*current_)->to_string());
        return true;
    }
}

std::string MovementAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

bool MovementAction::empty_path()
{
    if(path_->empty()) {
        return true;
    }
    return false;

}

