#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "actions/rotate_action.h"

#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
#include "level.h"
#include "movement.h"
#include "point.h"
#include "pathfinder_hex.h"
#include "pathfinder_square.h"
#include "utils/logger.h"
#include "entity.h"

RotateAction::RotateAction(double direction)
{
    direction_ = direction;
}
RotateAction::RotateAction(Entity * entity, Point mouse_point)
{
    Vector vector = Vector(Point(entity->x_position(), entity->y_position()), mouse_point);
    direction_ = vector.direction();
}


std::string RotateAction::to_string()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::string_stream << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

bool RotateAction::update(Entity * entity, int delta_ticks)
{
    bool return_value = true;

    // Grab variables from entity to manipulate here, will update them at end
    double rotation = entity->rotation();

    if(delta_ticks <= 0) {
        return return_value;
    }

    bool clockwise = false;
    double direction_degrees = 0;

    // Check rotation
    if(rotation != direction_) {
        Logger::write(Logger::string_stream << "Rotation: " << rotation << ", Direction: " << direction_);
        // Determine and set rotation direction
        double dir = direction_ - rotation;
        if((dir > 0) && (std::abs(dir) <= 180)) { clockwise = false; }
        if((dir > 0) && (std::abs(dir) > 180)) { clockwise = true; }
        if((dir < 0) && (std::abs(dir) <= 180)) { clockwise = true; }
        if((dir < 0) && (std::abs(dir) > 180)) { clockwise = false; }

        //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
        if(dir > 180) {
            dir -= 360;
        }
        else if(dir < -180) {
            dir += 360;
        }

        direction_degrees = std::abs(dir);

        double degrees = kEntityRotationVelocity * (delta_ticks / 1000.f);
        // Turn CW
        if(clockwise) {
            rotation -= degrees;
        }
        // Turn CCW
        else {
            rotation += degrees;
        }

        // check if turned far enough
        direction_degrees = direction_degrees - degrees;
        if(direction_degrees < 0) {
            rotation = direction_;
            return_value = false;
        }
    }

    // Update new values of variables
    entity->set_rotation(rotation);

    return return_value;
}

void RotateAction::stop()
{

}

bool RotateAction::facing(Entity * entity, Entity * target)
{
    Vector vector = Vector(entity->position(), target->position());
    if(entity->rotation() != vector.direction()) {
        return false;
    }

    return true;
}

