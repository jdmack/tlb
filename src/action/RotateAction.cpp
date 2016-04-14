#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "action/RotateAction.h"

#include "GameObject.h"
#include "Grid.h"
#include "GridNode.h"
#include "Level.h"
#include "Movement.h"
#include "Point.h"
#include "PathfinderHex.h"
#include "PathfinderSquare.h"
#include "util/Logger.h"
#include "Entity.h"

RotateAction::RotateAction(double direction)
{
    direction_ = direction;
}
RotateAction::RotateAction(Entity * entity, Point mousePoint)
{
    Vector vector = Vector(Point(entity->xPosition(), entity->yPosition()), mousePoint);
    direction_ = vector.direction();
    Logger::write(Logger::ss << "RotateAction - " << mousePoint.toString() << " - " << direction_);
}


std::string RotateAction::toString()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::ss << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

bool RotateAction::update(Entity * entity, int deltaTicks)
{
    bool returnValue = true;

    // Grab variables from entity to manipulate here, will update them at end
    double rotation = entity->rotation();

    if(deltaTicks <= 0) {
        return returnValue;
    }

    bool clockwise = false;
    double directionDegrees = 0;

    // Check rotation
    if(rotation != direction_) {
        //Logger::write(Logger::ss << "Rotation: " << rotation << ", Direction: " << direction_);
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

        directionDegrees = std::abs(dir);

        double degrees = kEntityRotationVelocity * (deltaTicks / 1000.f);
        // Turn CW
        if(clockwise) {
            rotation -= degrees;
        }
        // Turn CCW
        else {
            rotation += degrees;
        }

        // check if turned far enough
        directionDegrees = directionDegrees - degrees;
        if(directionDegrees < 0) {
            rotation = direction_;
            returnValue = false;
        }
    }

    // Update new values of variables
    entity->setRotation(rotation);

    return returnValue;
}

void RotateAction::stop()
{

}

bool RotateAction::facing(Entity * entity, Entity * target, double arc)
{
    Vector vector = Vector(entity->position(), target->position());


    double eDir = entity->rotation();
    double tDir = vector.direction();

    double diff = std::abs(eDir - tDir);

    if(diff >= 180) {
        diff = std::abs(diff - 360);
    }

    // Check a firing arc of 60 degrees
    if(std::abs(diff <= arc)) {
        return true;
    }
    else {
        return false;
    }

    //if(entity->rotation() != vector.direction()) {
    //    return false;
    //}
    return true;
}

