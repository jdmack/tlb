#include "game_object.h"
#include "renderer.h"
#include "utils/logger.h"
#include "vector.h"
#include "actions/action.h"
#include "sprite.h"
#include "game.h"
#include "movement.h"
#include "camera.h"

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

    current_action_ = nullptr;
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

    current_action_ = nullptr;
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

void GameObject::render()
{
    sprite_->render();

    // Draw line showing movement command
    /*
    if((current_action_ != nullptr) && (current_action_->is_movement())) {
        SDL_SetRenderDrawColor(game_->renderer()->renderer(), 0, 255, 0, 0);
        SDL_RenderDrawLine(game_->renderer()->renderer(), game_->camera()->x_adjust(x_position_), game_->camera()->y_adjust(y_position_), game_->camera()->x_adjust((static_cast<Movement*>(current_action_))->destination().x()), game_->camera()->y_adjust((static_cast<Movement*>(current_action_))->destination().y()));
    }
    */
}

bool GameObject::contains_point(double x, double y)
{
    Logger::write("GameObject::contains_point");
    return true;
}

void GameObject::select()
{
    Logger::write("GameObject::select");
    if(!selected_) {
        selected_ = true;

        // TODO (2013-08-26/JM) Put back in the select graphic code
        //SDL_Surface * select_surface = renderer_->load_image_alpha(kAssetArtDotCircle);
        //renderer_->apply_surface(0, 0, select_surface, surface_);
        //SDL_FreeSurface(select_surface);
    }
}

void GameObject::deselect()
{
    Logger::write("GameObject::deselect");
    if(selected_) {
        selected_ = false;

        // TODO (2013-08-26/JM) Put back in the select graphic code
        //SDL_FreeSurface(surface_);
        //surface_ = nullptr;
        //surface_ = renderer_->load_image_alpha(art_asset_);
    }
}

void GameObject::move(double x, double y)
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

