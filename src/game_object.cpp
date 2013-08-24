#include "game_object.h"
#include "screen.h"

GameObject::GameObject(std::string art_asset)
{
    art_asset_ = art_asset;
    x_position_ = 0;
    y_position_ = 0;

    surface_ = nullptr;
}

void GameObject::draw(Screen screen)
{


}
