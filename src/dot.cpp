#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#include "dot.h"
#include "assets.h"
#include "util/logger.h"
#include "screen.h"
#include "coordinate.h"
#include "vector.h"
#include "movement.h"
#include "sprite.h"

Dot::Dot()
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_ = kDotWidth;
    height_ = kDotHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtDot, kAssetArtDotCircle);
}

Dot::Dot(double x, double y, double rot) : GameObject(x,y, rot)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_ = kDotWidth;
    height_ = kDotHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtDot, kAssetArtDotCircle);
    sprite_->set_rotation(rot);
}



void Dot::update(int delta_ticks)
{
    if((x_velocity_ == 0) && (x_velocity_ == 0)) {
        return;
    }

    if((current_action_ != nullptr) && (current_action_->is_movement())) {

        Movement * movement_command = (static_cast<Movement*>(current_action_));

        // Check rotation
        if(rotation_ != movement_command->vector().direction()) {
            // rotate
            //double new_rotation = rotation_ + kDotRotationVelocity * (delta_ticks / 1000.f);
            rotation_ += kDotRotationVelocity * (delta_ticks / 1000.f);

            if(rotation_ > movement_command->vector().direction()) {
                rotation_ = movement_command->vector().direction();
            }
        }
        else {

            // Move left/right
            x_position_ += x_velocity_ * (delta_ticks / 1000.f);

            // Check left boundary
            if(x_position_ - (width_ / 2) < 0) {
                x_position_ = 0 + (width_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
            }
            // Check right boundary
            else if(x_position_ + (width_ / 2) > kScreenWidth) {
                x_position_ = kScreenWidth - (width_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
            }

            // Move up/down
            y_position_ += y_velocity_ * (delta_ticks / 1000.f);

            // Check top boundary
            if(y_position_ - (height_ / 2) < 0) {
                y_position_ = 0 + (height_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
            }
            // Check bottom boundary
            else if(y_position_ + (height_ / 2) > kScreenHeight) {
                y_position_ = kScreenHeight - (height_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
            }

            double distance = Movement::calculate_distance(Coordinate(movement_command->destination().x_position(), movement_command->destination().y_position()), Coordinate(x_position_, y_position_));

            //Logger::write(Logger::string_stream << distance << " " << movement_command->distance());

            if(distance > movement_command->distance()) {
                x_position_ = movement_command->destination().x_position();
                y_position_ = movement_command->destination().y_position();
                x_velocity_ = 0;
                y_velocity_ = 0;

                delete(current_action_);
                current_action_ = nullptr;
            }
            else {
                movement_command->set_distance(distance);
            }
        }
    }
}

bool Dot::contains_point(double x, double y)
{
    if((x < (x_position_ - (width_ / 2))) || (x > (x_position_ + (width_ / 2)))) {
        return false;
    }
    else if((y < (y_position_ - (width_ / 2))) || (y > (y_position_ + (height_ / 2)))) {
        return false;
    }

    return true;
}

void Dot::select()
{
    Logger::write(Logger::string_stream << "Dot::select object_id: " << object_id_ << " (x,y): (" << x_position_ << ", " <<  y_position_ << ")");
    GameObject::select();
    sprite_->select();
}

void Dot::deselect()
{
    Logger::write("Dot::deselect");
    GameObject::deselect();
    sprite_->deselect();
}

void Dot::move(double x, double y)
{
    Logger::write("move command");

    current_action_ = new Movement(Vector(x_position_, y_position_, x, y), Coordinate(x, y));

    Movement * movement_command = static_cast<Movement*>(current_action_);
    movement_command->set_distance(Movement::calculate_distance(Coordinate(movement_command->destination().x_position(), movement_command->destination().y_position()), Coordinate(x_position_, y_position_)));

    Vector velocity(kDotVelocity, static_cast<Movement*>(current_action_)->vector().direction());

    x_velocity_ = velocity.x_component();
    y_velocity_ = velocity.y_component();

}

void Dot::stop()
{
    Logger::write("stop command");
    x_velocity_ = 0;
    y_velocity_ = 0;
}


