#include "camera.h"
#include "game_object.h"
#include "level.h"
#include "game.h"
#include "util/logger.h"

Camera::Camera(Game * game)
{
    x_position_ = kCameraInitialX;
    y_position_ = kCameraInitialY;
    width_ = kCameraWidth;
    height_ = kCameraHeight;

    game_ = game;
}

void Camera::move(double x, double y) {
    x_position_ = x;
    y_position_ = y;
    fix_bounds();
}

void Camera::center(GameObject * object)
{
    x_position_ = object->x_position() - (width_ / 2);
    y_position_ = object->y_position() - (height_ / 2);
    //Logger::write(Logger::string_stream << "Camera: " << x_position_ << "," << y_position_);
    fix_bounds();
    //Logger::write(Logger::string_stream << "Camera: " << x_position_ << "," << y_position_);
}

SDL_Rect Camera::rect()
{
    SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    return rect;
}

void Camera::fix_bounds()
{
    if(x_position_ < 0) {
        x_position_ = 0;
    }
    if(y_position_ < 0) {
        y_position_ = 0;
    }
    if(x_position_ > game_->level()->width() - width_) {
        x_position_ = game_->level()->width() - width_;
    }
    if(y_position_ > game_->level()->height() - height_) {
        y_position_ = game_->level()->height() - height_;
    }
}

bool Camera::contains(SDL_Rect rect)
{
    // bottom_A <= top_B
    if((y_position_ + height_) <= rect.y) {
        return false;
    }

    // top_A <= bottom_B
    if(y_position_ >= (rect.y + rect.h)) {
        return false;
    }

    // right_A <= left_B
    if((x_position_ + width_) <= rect.x) {
        return false;
    }

    // left_A <= right_B
    if(x_position_ >= (rect.x + rect.w)) {
        return false;
    }

    return true;
}

double Camera::x_adjust(double x)
{
    return x - x_position_;
}

double Camera::y_adjust(double y)
{
    return y - y_position_;
}

