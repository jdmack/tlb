#include <cmath>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "action/MoveAction.h"

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

MoveAction::MoveAction(Point start, Point end, Level * level)
{
    bool usePathfinding = true;

	start_ = start;
	end_ = end;
	level_ = level;
	started_ = false;

	type_ = ACTION_MOVE;

	path_ = new std::vector<Movement *>();

	if(usePathfinding) {
	    findPath();
	}
	else {
        // Create movement vector
        Vector vector = Vector(start, end);

        // Create movement
        Movement * thisMovement = new Movement(vector, start, end);
        path_->push_back(thisMovement);
        current_ = path_->begin();

	}
}

void MoveAction::findPath()
{
    bool hexGrid = false;
    // Create Pathfinder

	// Get path as list of nodes
	std::list<GridNode *> * nodes;

	GridNode * startNode = level_->grid()->nodeAtPoint(start_);
	GridNode * endNode = level_->grid()->nodeAtPoint(end_);

	if(hexGrid) {
        PathfinderHex pathfinder(level_->grid());
        nodes = pathfinder.run(startNode, endNode);
	}
	else {
        PathfinderSquare pathfinder(level_->grid());
        nodes = pathfinder.run(startNode, endNode);
	}
    // Print the path to log
	//Logger::ss << "Path: ";
	for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	    //Logger::ss << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	    //Logger::ss << (*iterator)->toString() << " ";
	}
	//Logger::write(Logger::ss);
    //Logger::write(Logger::ss << "# of nodes: " << nodes->size());

	// Convert node path into Movement path
    while(nodes->size() > 1) {
	    if(nodes->size() >= 2) {
            // TODO(2013-09-20/JM): Add code to filter straight line paths into a single movement

            GridNode * startNode = nodes->front();
            if(nodes->empty()) {
                //Logger::write(Logger::ss << "Uh oh, list is empty dude!\n");
                break;
            }
            nodes->pop_front();
            if(nodes->empty()) {
                //Logger::write(Logger::ss << "Uh oh, list is empty dude!\n");
                break;
            }
            GridNode * endNode = nodes->front();

            // Create movement vector
            Vector vector = Vector(startNode->centerPoint(), endNode->centerPoint());

            // Create movement
            //Logger::write(Logger::ss << "Start Point: " << startNode->centerPoint().toString());
            //Logger::write(Logger::ss << "End Point: " << endNode->centerPoint().toString());
            Movement * thisMovement = new Movement(vector, startNode->centerPoint(), endNode->centerPoint());

            path_->push_back(thisMovement);
        }
	    else {
            // shouldn't ever run this
            break;
	    }
	}

    // Check if entity is located at the cneter point of the start grid
    /*
    GridNode * startGrid = level_->grid()->nodeAtPoint(start_);
    Point startGridCenterPoint = startGrid->centerPoint();
    Movement * firstMovement = *path_->begin();

    if(startGridCenterPoint != start_) {
        Vector vector = Vector(start_, firstMovement->destination());
        firstMovement->setVector(vector);
        firstMovement->setStart(start_);
    }
*/

	// Set current movement to beginning
	current_ = path_->begin();
	if(!path_->empty()) {
	    //Logger::write(Logger::ss << "MoveAction::firstMovement(): " << (*current_)->toString());
	}
	//Logger::write(Logger::ss << "Path created: " << path_->size() << " movements");

	// reset grid
	level_->grid()->resetPathfinding();
}

bool MoveAction::nextMovement()
{
    current_++;
    if(current_ == path_->end()) {
        //Logger::write(Logger::ss << "MoveAction::nextMovement(): No more Movements");
        return false;
    }
    else {
        //Logger::write(Logger::ss << "MoveAction::nextMovement(): " << (*current_)->toString());
        return true;
    }
}

std::string MoveAction::toString()
{
	//for (std::list<GridNode *>::iterator iterator = nodes->begin(), end = nodes->end(); iterator != end; ++iterator) {
	//    Logger::ss << "(" << (**iterator).row() << ", " << (**iterator).column() << ") ";
	//}
	return "";
}

bool MoveAction::emptyPath()
{
    if(path_->empty()) {
        return true;
    }
    return false;

}

bool MoveAction::update(Entity * entity, int deltaTicks)
{
    bool correctDestination = false;
    bool returnValue = true;

    // Grab variables from entity to manipulate here, will update them at end
    double width = entity->width();
    double height = entity->height();
    double xPosition = entity->xPosition();
    double yPosition = entity->yPosition();
    double xVelocity = entity->xVelocity();
    double yVelocity = entity->yVelocity();
    double xAcceleration = entity->xAcceleration();
    double yAcceleration = entity->yAcceleration();
    double rotation = entity->rotation();

    if(started_ == false) {
        if(path_->size() <= 0) return false;
        started_ = true;
        currentMaxVelocity_ = Vector(entity->maximumSpeed(), (*current_)->vector().direction());
        xVelocity = currentMaxVelocity_.xComponent();
        yVelocity = currentMaxVelocity_.yComponent();
        entity->setXVelocity(xVelocity);
        entity->setYVelocity(yVelocity);

        //Vector acceleration(kEntityAcceleration, moveAction->current()->vector().direction());
        //xAcceleration_ = acceleration.xComponent();
        //yAcceleration_ = acceleration.yComponent();
    }

    if(deltaTicks <= 0) {
        return returnValue;
    }

    // Check rotation
    if(rotation != (*current_)->vector().direction()) {
        //Logger::write(Logger::ss << "Rotation: " << rotation << ", Direction: " << (*current_)->vector().direction());
        // Determine and set rotation direction
        double dir = (*current_)->vector().direction() - rotation;
        if((dir > 0) && (std::abs(dir) <= 180)) { (*current_)->setClockwise(false); }
        if((dir > 0) && (std::abs(dir) > 180)) { (*current_)->setClockwise(true); }
        if((dir < 0) && (std::abs(dir) <= 180)) { (*current_)->setClockwise(true); }
        if((dir < 0) && (std::abs(dir) > 180)) { (*current_)->setClockwise(false); }

        //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
        if(dir > 180) {
            dir -= 360;
        }
        else if(dir < -180) {
            dir += 360;
        }

        (*current_)->setDegrees(std::abs(dir));

        double degrees  = kEntityRotationVelocity * (deltaTicks / 1000.f);
        // Turn CW
        if((*current_)->clockwise()) {
            rotation -= degrees;
        }
        // Turn CCW
        else {
            rotation += degrees;
        }

        // check if turned far enough
        (*current_)->setDegrees((*current_)->degrees() - degrees);
        if((*current_)->degrees() < 0) {
            rotation = (*current_)->vector().direction();
        }
    }
    else {

        // Accelerate
        // TODO(2014-07-25/JM): Change use of maximumVelocity calls here to use speed variable in Entity
        //if((std::abs(xVelocity) < std::abs((*current_)->maximumVelocity().xComponent())) || ( std::abs(yVelocity) < std::abs((*current_)->maximumVelocity().yComponent())) ) {
        //    xVelocity += xAcceleration * (deltaTicks / 1000.f);
        //    yVelocity += yAcceleration * (deltaTicks / 1000.f);
        //}

        // Move left/right and up/down
        //xPosition += xVelocity * (deltaTicks / 1000.f);
        //yPosition += yVelocity * (deltaTicks / 1000.f);

        // Debugging version of movement code
        double xMovementAmount = xVelocity * (deltaTicks / 1000.f);
        xPosition += xMovementAmount;
        double yMovementAmount = yVelocity * (deltaTicks / 1000.f);
        yPosition += yMovementAmount;
        //Logger::write(Logger::ss << "Moving: (" << xMovementAmount << ", " << yMovementAmount << ")");

        // Check collisions
        //TODO(2013-09-05/JM): Create a rectangle class like SDL_Rect to replace all instances outside SDL specific code with it

        /*
        SDL_Rect rect;
        if(game_->level()->touchesWall(this, &rect)) {
            fixCollision(rect);
            Logger::write("STOPPING: Collision with wall");
            // Go back
            // TODO(2013-09-05/JM): Change this to move 1 pixel away from the collided object
            xPosition -= xVelocity * (deltaTicks / 1000.f);
            yPosition -= yVelocity * (deltaTicks / 1000.f);

            // TODO(2014-08-08/JM): Replace repeated instances of these 4 assignments to 0 with a better functionality
            //entity->stop();
            xVelocity = 0;
            yVelocity = 0;
            xAcceleration = 0;
            yAcceleration = 0;
        }
        else {
            // TODO(2013-09-05/JM): Create function for checking renderer boundary collisions
            // Check left boundary
            if(xPosition - (width / 2) < 0) {
                Logger::write("STOPPING: Collision with LEFT renderer boundary");

                //entity->stop();
                xVelocity = 0;
                yVelocity = 0;
                xAcceleration = 0;
                yAcceleration = 0;

                xPosition = 0 + (width / 2);
            }
            // Check right boundary
            else if(xPosition + (width / 2) > game_->level()->width()) {
                Logger::write("STOPPING: Collision with RIGHT renderer boundary");

                //entity->stop();
                xVelocity = 0;
                yVelocity = 0;
                xAcceleration = 0;
                yAcceleration = 0;

                xPosition = game_->level()->width() - (width / 2);
            }

            // Check top boundary
            if(yPosition - (height / 2) < 0) {
                Logger::write("STOPPING: Collision with TOP renderer boundary");

                //entity->stop();
                xVelocity = 0;
                yVelocity = 0;
                xAcceleration = 0;
                yAcceleration = 0;

                yPosition = 0 + (height / 2);
            }
            // Check bottom boundary
            else if(yPosition + (height / 2) > game_->level()->height()) {
                Logger::write("STOPPING: Collision with BOTTOM renderer boundary");

                //entity->stop();
                xVelocity = 0;
                yVelocity = 0;
                xAcceleration = 0;
                yAcceleration = 0;

                yPosition = game_->level()->height() - (height / 2);
            }

        }
        */
        bool pastPoint = false;

        if((xVelocity > 0) && (yVelocity > 0)) {
            if((xPosition >= (*current_)->destination().x()) || (yPosition >= (*current_)->destination().y())) {
                //Logger::write("(x > 0) (y > 0)");
                pastPoint = true;
            }
        }
        else if((xVelocity > 0) && (yVelocity < 0)) {
            if((xPosition >= (*current_)->destination().x()) || (yPosition <= (*current_)->destination().y())) {
                //Logger::write("(x > 0) (y < 0)");
                pastPoint = true;
            }
        }
        else if((xVelocity < 0) && (yVelocity > 0)) {
            if((xPosition <= (*current_)->destination().x()) || (yPosition >= (*current_)->destination().y())) {
                //Logger::write("(x < 0) (y > 0)");
                pastPoint = true;
            }
        }
        else if((xVelocity < 0) && (yVelocity < 0)) {
            if((xPosition <= (*current_)->destination().x()) || (yPosition <= (*current_)->destination().y())) {
                //Logger::write("(x < 0) (y < 0)");
                pastPoint = true;
            }
        }
        else if(xVelocity == 0) {
            if(yVelocity > 0) {
                if(yPosition >= (*current_)->destination().y()) {
                    //Logger::write("(x == 0) (y > 0)");
                    pastPoint = true;
                }
            }
            else if(yVelocity < 0) {
                if(yPosition <= (*current_)->destination().y()) {
                    //Logger::write("(x == 0) (y < 0)");
                    pastPoint = true;
                }
            }
        }
        else if(yVelocity == 0) {
            if(xVelocity > 0) {
                if(xPosition >= (*current_)->destination().x()) {
                    //Logger::write("(x > 0) (y == 0)");
                    pastPoint = true;
                }
            }
            else if(xVelocity < 0) {
                if(xPosition <= (*current_)->destination().x()) {
                    //Logger::write("(x < 0) (y == 0)");
                    pastPoint = true;
                }
            }
        }

        if(pastPoint) {
            //Logger::write("STOPPING: Moved past point");

            xVelocity = 0;
            yVelocity = 0;
            xAcceleration = 0;
            yAcceleration = 0;

            if(correctDestination) {
                xPosition = (*current_)->destination().x();
                yPosition = (*current_)->destination().y();
            }
            //Logger::write(Logger::ss << "Destination:" << (*current_)->destination().toString());
        }

        if(entity->stopped()) {
            if(nextMovement()) {
                currentMaxVelocity_ = Vector(entity->maximumSpeed(), (*current_)->vector().direction());
                xVelocity = currentMaxVelocity_.xComponent();
                yVelocity = currentMaxVelocity_.yComponent();
            }
            else {
                returnValue = false;
                //Logger::write(Logger::ss << "Actual Dest: (" << xPosition << ", " << yPosition << ")");
            }
        }
    }
    // TODO(2014-08-14/JM): I believe the small pause we notice between Movements is because of going past the movement destination. We move back to the destination
    // and then don't utilitize all that wasted distance we moved during that frame
    //Logger::write(Logger::ss << "Current Pos: (" << xPosition << ", " << yPosition << ")");

    // Update new values of variables
    entity->setWidth(width);
    entity->setHeight(height);
    entity->setXPosition(xPosition);
    entity->setYPosition(yPosition);
    entity->setXVelocity(xVelocity);
    entity->setYVelocity(yVelocity);
    entity->setXAcceleration(xAcceleration);
    entity->setYAcceleration(yAcceleration);
    entity->setRotation(rotation);

    return returnValue;
}

void MoveAction::stop()
{
    std::vector<Movement *>::iterator mIterator = current_;
    if(mIterator != path_->end()) {

        mIterator++;

        while(mIterator != path_->end()) {
            Movement * movement = *mIterator;
            mIterator = path_->erase(mIterator);
            delete movement;
        }
    }
}

void MoveAction::removeMovementsBack(int number)
{
    for(int i = 0; i < number; i++) {

        if(path_->size() <= 0) {
            return;
        }
        Movement * thisMovement = path_->back();
        path_->pop_back();
        delete thisMovement;
    }
}

