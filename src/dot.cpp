#include <cmath>

#include "SDL2/SDL.h"

#include "dot.h"
#include "assets.h"
#include "point.h"
#include "game.h"
#include "level.h"
#include "movement.h"
#include "screen.h"
#include "sprite.h"
#include "vector.h"
#include "utils/logger.h"

Dot::Dot(Game * game) : GameObject(game)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kDotWidth;
    height_ = kDotHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
}

Dot::Dot(Game * game, double x, double y, double rot) : GameObject(game, x, y, rot)
{
    x_velocity_ = 0;
    y_velocity_ = 0;

    width_  = kDotWidth;
    height_ = kDotHeight;

    selectable_ = true;
    sprite_ = new Sprite(this, kAssetArtHexagon, kAssetArtHexagonOutline);
}

void Dot::update(int delta_ticks)
{
    if((x_velocity_ == 0) && (y_velocity_ == 0)) {
        if((x_acceleration_ == 0) && (y_acceleration_ == 0)) {
            return;
        }
    }

    // TODO(2013-09-06/JM): Bug: Moving only on 1 axis causes a jump
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

            // Accelerate
            if((std::abs(x_velocity_) < std::abs(movement_command->maximum_velocity().x_component())) || ( std::abs(y_velocity_) < std::abs(movement_command->maximum_velocity().y_component())) ) {
                x_velocity_ += x_acceleration_ * (delta_ticks / 1000.f);
                y_velocity_ += y_acceleration_ * (delta_ticks / 1000.f);
            }

            // Move left/right
            x_position_ += x_velocity_ * (delta_ticks / 1000.f);

            // Move up/down
            y_position_ += y_velocity_ * (delta_ticks / 1000.f);

            // Check collisions
            //TODO(2013-09-05/JM): Create a rectangle class like SDL_Rect to replace all instances outside SDL specific code with it
            SDL_Rect rect;
            if(game_->level()->touches_wall(this, &rect)) {
                fix_collision(rect);
                Logger::write("STOPPING: Collision with wall");
                // Go back
                // TODO(2013-09-05/JM): Change this to move 1 pixel away from the collided object
                x_position_ -= x_velocity_ * (delta_ticks / 1000.f);
                y_position_ -= y_velocity_ * (delta_ticks / 1000.f);

                stop();
            }
            else {
                // TODO(2013-09-05/JM): Create function for checking screen boundary collisions
                // Check left boundary
                if(x_position_ - (width_ / 2) < 0) {
                    Logger::write("STOPPING: Collision with LEFT screen boundary");
                    stop();
                    x_position_ = 0 + (width_ / 2);
                }
                // Check right boundary
                else if(x_position_ + (width_ / 2) > game_->level()->width()) {
                    Logger::write("STOPPING: Collision with RIGHT screen boundary");
                    stop();
                    x_position_ = game_->level()->width() - (width_ / 2);
                }

                // Check top boundary
                if(y_position_ - (height_ / 2) < 0) {
                    Logger::write("STOPPING: Collision with TOP screen boundary");
                    stop();
                    y_position_ = 0 + (height_ / 2);
                }
                // Check bottom boundary
                else if(y_position_ + (height_ / 2) > game_->level()->height()) {
                    Logger::write("STOPPING: Collision with BOTTOM screen boundary");
                    stop();
                    y_position_ = game_->level()->height() - (height_ / 2);
                }

                double distance = Movement::calculate_distance(Point(movement_command->destination().x(), movement_command->destination().y()), Point(x_position_, y_position_));

                if(distance > movement_command->distance()) {
                    Logger::write("STOPPING: Movement distance travelled");
                    stop();
                    x_position_ = movement_command->destination().x();
                    y_position_ = movement_command->destination().y();
                }
                else {
                    movement_command->set_distance(distance);
                }
            }

            if(stopped()) {
                delete current_action_;
                current_action_ = nullptr;
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
    bool currently_moving = false;
    if(current_action_ != nullptr) {
        currently_moving = true;
    }

	// Create MovementAction
    Vector vector = Vector(x_position_, y_position_, x, y);
    Point point = Point(x, y);
    current_action_ = new Movement(vector, point);
    Movement * movement_command = static_cast<Movement*>(current_action_);

    // Set distance to destination
    movement_command->set_distance(Movement::calculate_distance(Point(movement_command->destination().x(), movement_command->destination().y()), Point(x_position_, y_position_)));

    // Determine and set rotation direction
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

    if(currently_moving) {
        // TODO(2013-09-19/JM): Change this to instead check what the total velocity was and use that as
        // it currently instantly accelerates to full speed even if it's barely moving when you click a new move
        // Write a function (possibly a Velocity class) to return total velocity when given x/y components
        x_velocity_ = movement_command->maximum_velocity().x_component();
        y_velocity_ = movement_command->maximum_velocity().y_component();
    }
    else {
        x_velocity_ = 0;
        y_velocity_ = 0;
        x_acceleration_ = acceleration.x_component();
        y_acceleration_ = acceleration.y_component();
    }
    Logger::write(Logger::string_stream << "Move - (x,y): (" << movement_command->destination().x() << "," << movement_command->destination().y()
            << ") direction: " << movement_command->vector().direction());

}
