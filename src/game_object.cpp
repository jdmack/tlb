#include "game_object.h"
#include "screen.h"

GameObject::GameObject(std::string art_asset)
{
    art_asset_ = art_asset;
    x_position_ = 0;
    y_position_ = 0;

    surface_ = nullptr;
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
