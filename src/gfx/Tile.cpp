#include "gfx/Tile.h"
#include "Level.h"
#include "gfx/Camera.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "Point.h"
#include "gfx/Tileset.h"
#include "Frame.h"

Tile::Tile()
{
    xPosition_ = 0;
    yPosition_ = 0;
    width_ = 0;
    height_ = 0;
    type_ = 0;

    row_ = -1;
    column_ = -1;
    tileset_ = nullptr;
}

Tile::Tile(Point position, double width, double height, int type)
{
    xPosition_ = position.x();
    yPosition_ = position.y();
    width_ = width;
    height_ = height;
    type_ = type;

    row_ = yPosition_ / width_;
    column_ = xPosition_ / height_;
    tileset_ = nullptr;
}


SDL_Rect Tile::box()
{
    //SDL_Rect rect = { (int)xPosition_, (int)yPosition_, (int)width_, (int)height_ };
    Point point = Point(xPosition_, yPosition_);
    //point = level_->game()->renderer()->convertToIsometric(point);
    //point = level_->game()->renderer()->convertToCartesian(point);
    SDL_Rect rect = { (int)point.x(), (int)point.y(), (int)width_, (int)height_ };
    return rect;
}

void Tile::render(Frame * frame)
{
    /*
    if(Game::instance()->renderer()->camera()->contains(box())) {
        SDL_Rect offset = box();
        SDL_Rect clip = tileset_->clips(type_);
        //Game::instance()->renderer()->renderTexture(tileset_->texture(), &offset, &clip);
        Game::instance()->renderer()->renderTextureFrame(tileset_->texture(), frame, &offset, &clip);
    }
    */
}
