#include "tile.h"
#include "level.h"
#include "camera.h"
#include "renderer.h"
#include "game.h"
#include "point.h"
#include "tileset.h"
#include "frame.h"

Tile::Tile()
{
    x_position_ = 0;
    y_position_ = 0;
    width_ = 0;
    height_ = 0;
    type_ = 0;

    row_ = -1;
    column_ = -1;
    tileset_ = nullptr;
}

Tile::Tile(Point position, double width, double height, int type)
{
    x_position_ = position.x();
    y_position_ = position.y();
    width_ = width;
    height_ = height;
    type_ = type;

    row_ = y_position_ / width_;
    column_ = x_position_ / height_;
    tileset_ = nullptr;
}


SDL_Rect Tile::box()
{
    //SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    Point point = Point(x_position_, y_position_);
    //point = level_->game()->renderer()->convert_to_isometric(point);
    //point = level_->game()->renderer()->convert_to_cartesian(point);
    SDL_Rect rect = { (int)point.x(), (int)point.y(), (int)width_, (int)height_ };
    return rect;
}

void Tile::render(Frame * frame)
{
    if(Game::instance()->renderer()->camera()->contains(box())) {
        SDL_Rect offset = box();
        SDL_Rect clip = tileset_->clips(type_);
        //Game::instance()->renderer()->render_texture(tileset_->texture(), &offset, &clip);
        Game::instance()->renderer()->render_texture_frame(tileset_->texture(), frame, &offset, &clip);
    }
}
