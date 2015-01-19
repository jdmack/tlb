#include "game_object.h"
#include "renderer.h"
#include "util/logger.h"
#include "vector.h"
#include "sprite.h"
#include "game.h"
#include "movement.h"
#include "camera.h"
#include "frame.h"

// TODO (2013-08-26/JM): Refactor constructor to use constructor delegation when
// you get a gcc 4.7 compiler

int GameObject::id_counter_ = 1;

GameObject::GameObject(Game * game)
{
    x_position_ = 0;
    y_position_ = 0;
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
    rotation_ = 0;
    width_ = 0;
    height_ = 0;

    selectable_ = false;
    selected_ = false;

    object_id_ = id_counter_++;

    game_ = game;

    sprite_ = nullptr;
}

GameObject::GameObject(Game * game, Point position, double rot)
{
    x_position_ = position.x();
    y_position_ = position.y();
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
    rotation_ = rot;
    width_ = 0;
    height_ = 0;

    selectable_ = false;
    selected_ = false;

    object_id_ = id_counter_++;

    game_ = game;

    sprite_ = nullptr;

}

GameObject::~GameObject()
{

}

void GameObject::create_sprite(std::string asset)
{
    // TODO(2014-08-20/JM): Get rid of the selection asset string
    sprite_ = new Sprite(this, asset, asset);
}

void GameObject::render(Frame * frame)
{
    sprite_->render(frame);
    x_abs_ = x_position_ + frame->x();
    y_abs_ = y_position_ + frame->y();
}

bool GameObject::contains_point(double x, double y)
{
    Logger::write("GameObject::contains_point");
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

SDL_Rect GameObject::rect()
{
    SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    return rect;
}

bool GameObject::check_collision(SDL_Rect rect)
{
    double this_top = y_position_ - (height_ / 2);
    double this_bottom = y_position_ + (height_ / 2);
    double this_left = x_position_ - (width_ / 2);
    double this_right = x_position_ + (width_ / 2);

    double other_top = rect.y;
    double other_bottom = rect.y + rect.h;
    double other_left = rect.x;
    double other_right = rect.x + rect.w;


    if(this_top >= other_bottom) {
        return false;
    }

    if(this_bottom <= other_top) {
        return false;
    }


    if(this_left >= other_right) {
        return false;
    }

    if(this_right <= other_left) {
        return false;
    }

    return true;
}
// TODO(2013-09-05/JM): Create a colission class to add to all objects to use for top/bottom/left/right/etc boundaries instead of always doing this x + (w/2) stuff
void GameObject::fix_collision(SDL_Rect rect)
{
    //if(x_velocity_ >
// TODO(2013-09-05/JM): Finish this function



}

Point GameObject::position()
{
    position_ = Point(x_position_, y_position_);
    return position_;
}

void GameObject::set_position(Point position)
{
    position_ = position;
    x_position_ = position_.x();
    y_position_ = position_.y();
}

