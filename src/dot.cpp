#include <cmath>
#include "SDL/SDL.h"
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
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
}

Dot::Dot(double x, double y, double rot) : GameObject(x,y, rot)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_ = kDotWidth;
    height_ = kDotHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
    // TODO(2013-09-01/JM): Set rotation
    //sprite_->set_rotation(rot);
}

void Dot::update(int delta_ticks)
{
    if((x_velocity_ == 0) && (y_velocity_ == 0)) {
        if((x_acceleration_ == 0) && (y_acceleration_ == 0)) {
            return;
        }
    }

    if((current_action_ != nullptr) && (current_action_->is_movement())) {

        Movement * movement_command = (static_cast<Movement*>(current_action_));

        // Check rotation
        if(rotation_ != movement_command->vector().direction()) {

            double degrees  = kDotRotationVelocity * (delta_ticks / 1000.f);
            // Turn CW
            if(movement_command->clockwise()) {
                rotation_ -= degrees;
            }
            // Turn CCW
            else {
                rotation_ += degrees;
            }

            // check if turned far enough
            movement_command->set_degrees(movement_command->degrees() - degrees);
            if(movement_command->degrees() < 0) {
                rotation_ = movement_command->vector().direction();
            }
        }
        else {

            if( (std::abs(x_velocity_) < std::abs(movement_command->maximum_velocity().x_component())) || ( std::abs(y_velocity_) < std::abs(movement_command->maximum_velocity().y_component())) ) {
                x_velocity_ += x_acceleration_ * (delta_ticks / 1000.f);
                y_velocity_ += y_acceleration_ * (delta_ticks / 1000.f);
            }

            // Move left/right
            x_position_ += x_velocity_ * (delta_ticks / 1000.f);

            // Move up/down
            y_position_ += y_velocity_ * (delta_ticks / 1000.f);


            // Check left boundary
            if(x_position_ - (width_ / 2) < 0) {
                x_position_ = 0 + (width_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
                x_acceleration_ = 0;
                y_acceleration_ = 0;
            }
            // Check right boundary
            else if(x_position_ + (width_ / 2) > kScreenWidth) {
                x_position_ = kScreenWidth - (width_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
                x_acceleration_ = 0;
                y_acceleration_ = 0;
            }

            // Check top boundary
            if(y_position_ - (height_ / 2) < 0) {
                y_position_ = 0 + (height_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
                x_acceleration_ = 0;
                y_acceleration_ = 0;
            }
            // Check bottom boundary
            else if(y_position_ + (height_ / 2) > kScreenHeight) {
                y_position_ = kScreenHeight - (height_ / 2);
                x_velocity_ = 0;
                y_velocity_ = 0;
                x_acceleration_ = 0;
                y_acceleration_ = 0;
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
    //if((x < x_position_) || (x > x_position_ + width_)) {
    if((x < (x_position_ - (width_ / 2))) || (x > (x_position_ + (width_ / 2)))) {
        return false;
    }
    //else if((y < y_position_) || (y > y_position_ + height_)) {
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

    double dir = movement_command->vector().direction() - rotation_;
    if((dir > 0) && (std::abs(dir) <= 180)) { movement_command->set_clockwise(false); }
    if((dir > 0) && (std::abs(dir) > 180)) { movement_command->set_clockwise(true); }
    if((dir < 0) && (std::abs(dir) <= 180)) { movement_command->set_clockwise(true); }
    if((dir < 0) && (std::abs(dir) > 180)) { movement_command->set_clockwise(false); }

    //dir += (dir > 180) ? -360 : (dir < -180) ? 360 : 0;
    if(dir > 180) {
        dir -= 360;
    }
    else if(dir < -180) {
        dir += 360;
    }
    movement_command->set_degrees(std::abs(dir));

    Vector acceleration(kDotAcceleration, movement_command->vector().direction());

    movement_command->set_maximum_velocity(Vector(kDotVelocity, movement_command->vector().direction()));

    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = acceleration.x_component();
    y_acceleration_ = acceleration.y_component();
    Logger::write(Logger::string_stream << "Move - (x,y): (" << movement_command->destination().x_position() << "," << movement_command->destination().x_position()
            << ") direction: " << movement_command->vector().direction());

}

void Dot::stop()
{
    Logger::write("stop command");
    x_velocity_ = 0;
    y_velocity_ = 0;
    x_acceleration_ = 0;
    y_acceleration_ = 0;
}


