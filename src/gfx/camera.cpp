#include "gfx/camera.h"
#include "gameObject.h"
#include "level.h"
#include "game.h"
#include "util/logger.h"
#include "point.h"
#include "util/math/math.h"

Camera::Camera()
{
    xPosition_ = kCameraInitialX;
    yPosition_ = kCameraInitialY;

    width_ = kCameraWidth;
    height_ = kCameraHeight;
}

void Camera::move(double x, double y) {
    xPosition_ = x;
    yPosition_ = y;
    fixBounds();
}

void Camera::center(GameObject * object)
{
    xPosition_ = object->xPosition() - (width_ / 2);
    yPosition_ = object->yPosition() - (height_ / 2);
    //Logger::write(Logger::ss << "Camera: " << xPosition_ << "," << yPosition_);
    fixBounds();
    //Logger::write(Logger::ss << "Camera: " << xPosition_ << "," << yPosition_);
}

SDL_Rect Camera::rect()
{
    SDL_Rect rect = { (int)xPosition_, (int)yPosition_, (int)width_, (int)height_ };
    return rect;
}

void Camera::fixBounds()
{
    if(xPosition_ < 0) {
        xPosition_ = 0;
    }
    if(yPosition_ < 0) {
        yPosition_ = 0;
    }
    if(xPosition_ > Game::instance()->level()->width() - width_) {
        xPosition_ = Game::instance()->level()->width() - width_;
    }
    if(yPosition_ > Game::instance()->level()->height() - height_) {
        yPosition_ = Game::instance()->level()->height() - height_;
    }
}

bool Camera::contains(SDL_Rect rect)
{
    // bottom_A <= top_B
    if((yPosition_ + height_) <= rect.y) {
        return false;
    }

    // top_A <= bottom_B
    if(yPosition_ >= (rect.y + rect.h)) {
        return false;
    }

    // right_A <= left_B
    if((xPosition_ + width_) <= rect.x) {
        return false;
    }

    // left_A <= right_B
    if(xPosition_ >= (rect.x + rect.w)) {
        return false;
    }

    return true;
}

double Camera::xAdjust(double x)
{
    return x - xPosition_;
}

double Camera::yAdjust(double y)
{
    return y - yPosition_;
}


