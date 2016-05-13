#include "GameObject.h"
#include "gfx/Renderer.h"
#include "util/Logger.h"
#include "Vector.h"
#include "gfx/Sprite.h"
#include "Game.h"
#include "Movement.h"
#include "gfx/Camera.h"
#include "Frame.h"

// TODO (2013-08-26/JM): Refactor constructor to use constructor delegation when
// you get a gcc 4.7 compiler

int GameObject::idCounter_ = 1;

GameObject::GameObject()
{
    xPosition_ = 0;
    yPosition_ = 0;
    xVelocity_ = 0;
    yVelocity_ = 0;
    xAcceleration_ = 0;
    yAcceleration_ = 0;
    rotation_ = 0;
    width_ = 0;
    height_ = 0;

    selectable_ = false;
    selected_ = false;

    objectId_ = idCounter_++;

    xAbs_ = 0;
    yAbs_ = 0;
}

GameObject::GameObject(Point position, double rot)
{
    xPosition_ = position.x();
    yPosition_ = position.y();
    xVelocity_ = 0;
    yVelocity_ = 0;
    xAcceleration_ = 0;
    yAcceleration_ = 0;
    rotation_ = rot;
    width_ = 0;
    height_ = 0;

    selectable_ = false;
    selected_ = false;

    objectId_ = idCounter_++;

    xAbs_ = 0;
    yAbs_ = 0;

}

GameObject::~GameObject()
{

}

void GameObject::render()
{

}

bool GameObject::containsPoint(double x, double y)
{
    Logger::write("GameObject::containsPoint");
    return true;
}

void GameObject::select()
{
    Logger::write("GameObject::select");
    selected_ = true;
}

void GameObject::deselect()
{
    Logger::write("GameObject::deselect");
    selected_ = false;
}

void GameObject::move(Point point)
{
    // TODO(2013-08-27/JM): Handle rotating

}

bool GameObject::checkCollision(SDL_Rect rect)
{
    double thisTop = yPosition_ - (height_ / 2);
    double thisBottom = yPosition_ + (height_ / 2);
    double thisLeft = xPosition_ - (width_ / 2);
    double thisRight = xPosition_ + (width_ / 2);

    double otherTop = rect.y;
    double otherBottom = rect.y + rect.h;
    double otherLeft = rect.x;
    double otherRight = rect.x + rect.w;


    if(thisTop >= otherBottom) {
        return false;
    }

    if(thisBottom <= otherTop) {
        return false;
    }


    if(thisLeft >= otherRight) {
        return false;
    }

    if(thisRight <= otherLeft) {
        return false;
    }

    return true;
}
// TODO(2013-09-05/JM): Create a colission class to add to all objects to use for top/bottom/left/right/etc boundaries instead of always doing this x + (w/2) stuff
void GameObject::fixCollision(SDL_Rect rect)
{
    //if(xVelocity_ >
// TODO(2013-09-05/JM): Finish this function



}

Point GameObject::position()
{
    position_ = Point(xPosition_, yPosition_);
    return position_;
}

void GameObject::setPosition(Point position)
{
    position_ = position;
    xPosition_ = position_.x();
    yPosition_ = position_.y();
}

