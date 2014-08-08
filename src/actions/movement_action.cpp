#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "actions/movement_action.h"

#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
#include "level.h"
#include "movement.h"
#include "point.h"
#include "pathfinder.h"
#include "utils/logger.h"
#include "entity.h"

MovementAction::MovementAction(Point start, Point end, Level * level)
{
    bool use_pathfinding = true;

	start_ = start;
	end_ = end;
	level_ = level;
	started_ = false;

	type_ = ACTION_MOVEMENT;

	path_ = new std::vector<Movement *>();

	if(use_pathfinding) {
	    find_path();
	}
	else {
        // Create movement vector
        Vector vector = Vector(start, end);

        // Create movement
        Movement * this_movement = new Movement(vector, start, end);
        path_->push_back(this_movement);
        current_ = path_->begin();

	}
}

void MovementAction::find_path()
{
    // Create Pathfinder
	Pathfinder pathfinder(level_->grid());

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

bool MovementAction::update(Entity * entity, int delta_ticks)
{
    bool return_value = true;

    // Grab variables from entity to manipulate here, will update them at end
    double width = entity->width();
    double height = entity->height();
    double x_position = entity->x_position();
    double y_position = entity->y_position();
    double x_velocity = entity->x_velocity();
    double y_velocity = entity->y_velocity();
    double x_acceleration = entity->x_acceleration();
    double y_acceleration = entity->y_acceleration();
    double rotation = entity->rotation();

    if(started_ == false) {
        started_ = true;
        current_max_velocity_ = Vector(entity->maximum_speed(), (*current_)->vector().direction());
        x_velocity = current_max_velocity_.x_component();
        y_velocity = current_max_velocity_.y_component();
        entity->set_x_velocity(x_velocity);
        entity->set_y_velocity(y_velocity);

        //Vector acceleration(kEntityAcceleration, movement_action->current()->vector().direction());
        //x_acceleration_ = acceleration.x_component();
        //y_acceleration_ = acceleration.y_component();
    }

    if(delta_ticks <= 0) {
        return return_value;
    }

    // Check rotation
    if(rotation != (*current_)->vector().direction()) {
        Logger::write(Logger::string_stream << "Rotation: " << rotation << ", Direction: " << (*current_)->vector().direction());
        // Determine and set rotation direction
        double dir = (*current_)->vector().direction() - rotation;
        if((dir > 0) && (std::abs(dir) <= 180)) { (*current_)->set_clockwise(false); }
        if((dir > 0) && (std::abs(dir) > 180)) { (*current_)->set_clockwise(true); }
        if((dir < 0) && (std::abs(dir) <= 180)) { (*current_)->set_clockwise(true); }
        if((dir < 0) && (std::abs(dir) > 180)) { (*current_)->set_clockwise(false); }

        //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
        if(dir > 180) {
            dir -= 360;
        }
        else if(dir < -180) {
            dir += 360;
        }

        (*current_)->set_degrees(std::abs(dir));

        double degrees  = kEntityRotationVelocity * (delta_ticks / 1000.f);
        // Turn CW
        if((*current_)->clockwise()) {
            rotation -= degrees;
        }
        // Turn CCW
        else {
            rotation += degrees;
        }

        // check if turned far enough
        (*current_)->set_degrees((*current_)->degrees() - degrees);
        if((*current_)->degrees() < 0) {
            rotation = (*current_)->vector().direction();
        }
    }
    else {

        // Accelerate
        // TODO(2014-07-25/JM): Change use of maximum_velocity calls here to use speed variable in Entity
        //if((std::abs(x_velocity) < std::abs((*current_)->maximum_velocity().x_component())) || ( std::abs(y_velocity) < std::abs((*current_)->maximum_velocity().y_component())) ) {
        //    x_velocity += x_acceleration * (delta_ticks / 1000.f);
        //    y_velocity += y_acceleration * (delta_ticks / 1000.f);
        //}

        // Move left/right and up/down
        //x_position += x_velocity * (delta_ticks / 1000.f);
        //y_position += y_velocity * (delta_ticks / 1000.f);

        // Debugging version of movement code
        int x_movement_amount = x_velocity * (delta_ticks / 1000.f);
        x_position += x_movement_amount;
        int y_movement_amount = y_velocity * (delta_ticks / 1000.f);
        y_position += y_movement_amount;
        //Logger::write(Logger::string_stream << "Moving: (" << x_movement_amount << ", " << y_movement_amount << ")");

        // Check collisions
        //TODO(2013-09-05/JM): Create a rectangle class like SDL_Rect to replace all instances outside SDL specific code with it

        /*
        SDL_Rect rect;
        if(game_->level()->touches_wall(this, &rect)) {
            fix_collision(rect);
            Logger::write("STOPPING: Collision with wall");
            // Go back
            // TODO(2013-09-05/JM): Change this to move 1 pixel away from the collided object
            x_position -= x_velocity * (delta_ticks / 1000.f);
            y_position -= y_velocity * (delta_ticks / 1000.f);

            // TODO(2014-08-08/JM): Replace repeated instances of these 4 assignments to 0 with a better functionality
            //entity->stop();
            x_velocity = 0;
            y_velocity = 0;
            x_acceleration = 0;
            y_acceleration = 0;
        }
        else {
            // TODO(2013-09-05/JM): Create function for checking renderer boundary collisions
            // Check left boundary
            if(x_position - (width / 2) < 0) {
                Logger::write("STOPPING: Collision with LEFT renderer boundary");

                //entity->stop();
                x_velocity = 0;
                y_velocity = 0;
                x_acceleration = 0;
                y_acceleration = 0;

                x_position = 0 + (width / 2);
            }
            // Check right boundary
            else if(x_position + (width / 2) > game_->level()->width()) {
                Logger::write("STOPPING: Collision with RIGHT renderer boundary");

                //entity->stop();
                x_velocity = 0;
                y_velocity = 0;
                x_acceleration = 0;
                y_acceleration = 0;

                x_position = game_->level()->width() - (width / 2);
            }

            // Check top boundary
            if(y_position - (height / 2) < 0) {
                Logger::write("STOPPING: Collision with TOP renderer boundary");

                //entity->stop();
                x_velocity = 0;
                y_velocity = 0;
                x_acceleration = 0;
                y_acceleration = 0;

                y_position = 0 + (height / 2);
            }
            // Check bottom boundary
            else if(y_position + (height / 2) > game_->level()->height()) {
                Logger::write("STOPPING: Collision with BOTTOM renderer boundary");

                //entity->stop();
                x_velocity = 0;
                y_velocity = 0;
                x_acceleration = 0;
                y_acceleration = 0;

                y_position = game_->level()->height() - (height / 2);
            }

        }
        */
        bool past_point = false;

        if((x_velocity > 0) && (y_velocity > 0)) {
            if((x_position >= (*current_)->destination().x()) || (y_position >= (*current_)->destination().y())) {
                Logger::write("(x > 0) (y > 0)");
                past_point = true;
            }
        }
        else if((x_velocity > 0) && (y_velocity < 0)) {
            if((x_position >= (*current_)->destination().x()) || (y_position <= (*current_)->destination().y())) {
                Logger::write("(x > 0) (y < 0)");
                past_point = true;
            }
        }
        else if((x_velocity < 0) && (y_velocity > 0)) {
            if((x_position <= (*current_)->destination().x()) || (y_position >= (*current_)->destination().y())) {
                Logger::write("(x < 0) (y > 0)");
                past_point = true;
            }
        }
        else if((x_velocity < 0) && (y_velocity < 0)) {
            if((x_position <= (*current_)->destination().x()) || (y_position <= (*current_)->destination().y())) {
                Logger::write("(x < 0) (y < 0)");
                past_point = true;
            }
        }
        else if(x_velocity == 0) {
            if(y_velocity > 0) {
                if(y_position >= (*current_)->destination().y()) {
                    Logger::write("(x == 0) (y > 0)");
                    past_point = true;
                }
            }
            else if(y_velocity < 0) {
                if(y_position <= (*current_)->destination().y()) {
                    Logger::write("(x == 0) (y < 0)");
                    past_point = true;
                }
            }
        }
        else if(y_velocity == 0) {
            if(x_velocity > 0) {
                if(x_position >= (*current_)->destination().x()) {
                    Logger::write("(x > 0) (y == 0)");
                    past_point = true;
                }
            }
            else if(x_velocity < 0) {
                if(x_position <= (*current_)->destination().x()) {
                    Logger::write("(x < 0) (y == 0)");
                    past_point = true;
                }
            }
        }

        if(past_point) {
            Logger::write("STOPPING: Moved past point");

            x_velocity = 0;
            y_velocity = 0;
            x_acceleration = 0;
            y_acceleration = 0;

            x_position = (*current_)->destination().x();
            y_position = (*current_)->destination().y();
            Logger::write(Logger::string_stream << "Destination:" << (*current_)->destination().to_string());
        }

        if(entity->stopped()) {
            if(next_movement()) {
                current_max_velocity_ = Vector(entity->maximum_speed(), (*current_)->vector().direction());
                x_velocity = current_max_velocity_.x_component();
                y_velocity = current_max_velocity_.y_component();
            }
            else {
                return_value = false;
            }
        }
    }

    // Update new values of variables
    entity->set_width(width);
    entity->set_height(height);
    entity->set_x_position(x_position);
    entity->set_y_position(y_position);
    entity->set_x_velocity(x_velocity);
    entity->set_y_velocity(y_velocity);
    entity->set_x_acceleration(x_acceleration);
    entity->set_y_acceleration(y_acceleration);
    entity->set_rotation(rotation);

    return return_value;
}

void MovementAction::stop()
{
    std::vector<Movement *>::iterator m_iterator = current_;
    if(m_iterator != path_->end()) {

        m_iterator++;

        while(m_iterator != path_->end()) {
            Movement * movement = *m_iterator;
            m_iterator = path_->erase(m_iterator);
            delete movement;
        }
    }
}

