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
#include "entity.h"

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
        this_movement->set_maximum_velocity(Vector(kEntityVelocity, this_movement->vector().direction()));
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

            this_movement->set_maximum_velocity(Vector(kEntityVelocity, this_movement->vector().direction()));
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

void MovementAction::update(Entity * entity, int delta_ticks)
{
    /*
    if(delta_ticks <= 0) {
        return;
    }

    //if((x_velocity_ == 0) && (y_velocity_ == 0)) {
    //    if((x_acceleration_ == 0) && (y_acceleration_ == 0)) {
    //        return;
    //    }
    //}

    // TODO(2013-09-06/JM): Bug: Moving only on 1 axis causes a jump
    if((current_action_ != nullptr) && (current_action_->is_movement())) {
        //Logger::write(Logger::string_stream << "Entity Update - delta_ticks: " << delta_ticks);

        MovementAction * movement_command = (static_cast<MovementAction *>(current_action_));

        // Check rotation
        if(rotation_ != movement_command->current()->vector().direction()) {
            Logger::write(Logger::string_stream << "Rotation: " << rotation_ << ", Direction: " << movement_command->current()->vector().direction());
            // Determine and set rotation direction
            double dir = movement_command->current()->vector().direction() - rotation_;
            if((dir > 0) && (std::abs(dir) <= 180)) { movement_command->current()->set_clockwise(false); }
            if((dir > 0) && (std::abs(dir) > 180)) { movement_command->current()->set_clockwise(true); }
            if((dir < 0) && (std::abs(dir) <= 180)) { movement_command->current()->set_clockwise(true); }
            if((dir < 0) && (std::abs(dir) > 180)) { movement_command->current()->set_clockwise(false); }

            //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
            if(dir > 180) {
                dir -= 360;
            }
            else if(dir < -180) {
                dir += 360;
            }

            movement_command->current()->set_degrees(std::abs(dir));

            double degrees  = kEntityRotationVelocity * (delta_ticks / 1000.f);
            // Turn CW
            if(movement_command->current()->clockwise()) {
                rotation_ -= degrees;
            }
            // Turn CCW
            else {
                rotation_ += degrees;
            }

            // check if turned far enough
            movement_command->current()->set_degrees(movement_command->current()->degrees() - degrees);
            if(movement_command->current()->degrees() < 0) {
                rotation_ = movement_command->current()->vector().direction();
            }
        }
        else {

            // Accelerate
            //if((std::abs(x_velocity_) < std::abs(movement_command->current()->maximum_velocity().x_component())) || ( std::abs(y_velocity_) < std::abs(movement_command->current()->maximum_velocity().y_component())) ) {
            //    x_velocity_ += x_acceleration_ * (delta_ticks / 1000.f);
            //    y_velocity_ += y_acceleration_ * (delta_ticks / 1000.f);
            //}

            // Move left/right and up/down
            //x_position_ += x_velocity_ * (delta_ticks / 1000.f);
            //y_position_ += y_velocity_ * (delta_ticks / 1000.f);

            // Debugging version of movement code
            int x_movement_amount = x_velocity_ * (delta_ticks / 1000.f);
            x_position_ += x_movement_amount;
            int y_movement_amount = y_velocity_ * (delta_ticks / 1000.f);
            y_position_ += y_movement_amount;
            //Logger::write(Logger::string_stream << "Moving: (" << x_movement_amount << ", " << y_movement_amount << ")");

            // Check collisions
            //TODO(2013-09-05/JM): Create a rectangle class like SDL_Rect to replace all instances outside SDL specific code with it
            */
            /*
            SDL_Rect rect;
            if(game_->level()->touches_wall(this, &rect)) {
                fix_collision(rect);
                Logger::write("STOPPING: Collision with wall");
                // Go back
                // TODO(2013-09-05/JM): Change this to move 1 pixel away from the collided object
                x_position_ -= x_velocity_ * (delta_ticks / 1000.f);
                y_position_ -= y_velocity_ * (delta_ticks / 1000.f);

                stop();
            }
            else {
                // TODO(2013-09-05/JM): Create function for checking screen boundary collisions
                // Check left boundary
                if(x_position_ - (width_ / 2) < 0) {
                    Logger::write("STOPPING: Collision with LEFT screen boundary");
                    stop();
                    x_position_ = 0 + (width_ / 2);
                }
                // Check right boundary
                else if(x_position_ + (width_ / 2) > game_->level()->width()) {
                    Logger::write("STOPPING: Collision with RIGHT screen boundary");
                    stop();
                    x_position_ = game_->level()->width() - (width_ / 2);
                }

                // Check top boundary
                if(y_position_ - (height_ / 2) < 0) {
                    Logger::write("STOPPING: Collision with TOP screen boundary");
                    stop();
                    y_position_ = 0 + (height_ / 2);
                }
                // Check bottom boundary
                else if(y_position_ + (height_ / 2) > game_->level()->height()) {
                    Logger::write("STOPPING: Collision with BOTTOM screen boundary");
                    stop();
                    y_position_ = game_->level()->height() - (height_ / 2);
                }

            }
            */
            /*
            bool past_point = false;

            if((x_velocity_ > 0) && (y_velocity_ > 0)) {
                if((x_position_ >= movement_command->current()->destination().x()) || (y_position_ >= movement_command->current()->destination().y())) {
                    Logger::write("(x > 0) (y > 0)");
                    past_point = true;
                }
            }
            else if((x_velocity_ > 0) && (y_velocity_ < 0)) {
                if((x_position_ >= movement_command->current()->destination().x()) || (y_position_ <= movement_command->current()->destination().y())) {
                    Logger::write("(x > 0) (y < 0)");
                    past_point = true;
                }
            }
            else if((x_velocity_ < 0) && (y_velocity_ > 0)) {
                if((x_position_ <= movement_command->current()->destination().x()) || (y_position_ >= movement_command->current()->destination().y())) {
                    Logger::write("(x < 0) (y > 0)");
                    past_point = true;
                }
            }
            else if((x_velocity_ < 0) && (y_velocity_ < 0)) {
                if((x_position_ <= movement_command->current()->destination().x()) || (y_position_ <= movement_command->current()->destination().y())) {
                    Logger::write("(x < 0) (y < 0)");
                    past_point = true;
                }
            }
            else if(x_velocity_ == 0) {
                if(y_velocity_ > 0) {
                    if(y_position_ >= movement_command->current()->destination().y()) {
                        Logger::write("(x == 0) (y > 0)");
                        past_point = true;
                    }
                }
                else if(y_velocity_ < 0) {
                    if(y_position_ <= movement_command->current()->destination().y()) {
                        Logger::write("(x == 0) (y < 0)");
                        past_point = true;
                    }
                }
            }
            else if(y_velocity_ == 0) {
                if(x_velocity_ > 0) {
                    if(x_position_ >= movement_command->current()->destination().x()) {
                        Logger::write("(x > 0) (y == 0)");
                        past_point = true;
                    }
                }
                else if(x_velocity_ < 0) {
                    if(x_position_ <= movement_command->current()->destination().x()) {
                        Logger::write("(x < 0) (y == 0)");
                        past_point = true;
                    }
                }
            }


            if(past_point) {
                Logger::write("STOPPING: Moved past point");
                stop();
                x_position_ = movement_command->current()->destination().x();
                y_position_ = movement_command->current()->destination().y();
                Logger::write(Logger::string_stream << "Destination:" << movement_command->current()->destination().to_string());
            }

            if(stopped()) {
                if(movement_command->next_movement()) {
                    x_velocity_ = movement_command->current()->maximum_velocity().x_component();
                    y_velocity_ = movement_command->current()->maximum_velocity().y_component();
                }
                else {
                    delete current_action_;
                    current_action_ = nullptr;
                }
            }
        }
    }
*/
}
