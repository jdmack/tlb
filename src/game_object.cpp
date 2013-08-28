#include "game_object.h"
#include "screen.h"
#include "util/logger.h"

// TODO (2013-08-26/JM): Refactor constructor to use constructor delegation when
// you get a gcc 4.7 compiler

int GameObject::id_counter_ = 1;

GameObject::GameObject()
{
    x_position_ = 0;
    y_position_ = 0;
    rotation_ = 0;

    surface_ = nullptr;
    screen_ = nullptr;
    selectable_ = false;
    selected_ = false;

    object_id_ = id_counter_++;

}

GameObject::GameObject(float x, float y, float rot)
{
    x_position_ = x;
    y_position_ = y;
    rotation_ = rot;

    surface_ = nullptr;
    screen_ = nullptr;
    selectable_ = false;
    selected_ = false;

    object_id_ = id_counter_++;
}

GameObject::~GameObject()
{

}

void GameObject::draw(Screen * screen)
{
    screen->blit_surface((int)x_position_, (int)y_position_, surface_);
}

void GameObject::set_surface(SDL_Surface * surface)
{
    surface_ = surface;
}

std::string GameObject::art_asset()
{
    return art_asset_;
}

void GameObject::set_screen(Screen * screen)
{
    screen_ = screen;
}

bool GameObject::contains_point(float x, float y)
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
        //SDL_Surface * select_surface = screen_->load_image_alpha(kAssetArtDotCircle);
        //screen_->apply_surface(0, 0, select_surface, surface_);
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
        //surface_ = screen_->load_image_alpha(art_asset_);
    }
}

bool GameObject::selected()
{
    return selected_;
}

int GameObject::object_id()
{
    return object_id_;
}
