#include "camera.h"
#include "game_object.h"
#include "level.h"

Camera::Camera()
{
    x_position_ = kCameraInitialX;
    y_position_ = kCameraInitialY;
    width_ = kCameraWidth;
    height_ = kCameraHeight;

    level_ = nullptr;
}

Camera::Camera(Level * level)
{
    x_position_ = kCameraInitialX;
    y_position_ = kCameraInitialY;
    width_ = kCameraWidth;
    height_ = kCameraHeight;

    level_ = level;
}

void Camera::move(double x, double y) {
    x_position_ = x;
    y_position_ = y;
    fix_bounds();
}

void Camera::center(GameObject * object)
{
    x_position_ = object->x_position();
    y_position_ = object->y_position();
    fix_bounds();
}

SDL_Rect Camera::rect()
{
    SDL_Rect rect = { x_position_, y_position_, width_, height_ };
    return rect;
}

void Camera::fix_bounds()
{
    //Keep the camera in bounds.
    if( x_position_ < 0 )
    {
        x_position_ = 0;
    }
    if( y_position_ < 0 )
    {
        y_position_ = 0;
    }
    if( x_position_ > level_->width() - width_ )
    {
        x_position_ = level_->width() - width_;
    }
    if( y_position_ > level_->height() - height_ )
    {
        y_position_ = level_->height() - height_;
    }
}
