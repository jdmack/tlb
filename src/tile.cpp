#include "tile.h"
#include "level.h"
#include "camera.h"
#include "screen.h"
#include "game.h"

Tile::Tile()
{
    x_position_ = 0;
    y_position_ = 0;
    width_ = kTileWidth;
    height_ = kTileHeight;
    type_ = 0;
    level_ = nullptr;
}

Tile::Tile(double x, double y, int type, Level * level)
{
    x_position_ = x;
    y_position_ = y;
    width_ = kTileWidth;
    height_ = kTileHeight;
    type_ = type;

    level_ = level;

    clips_[kTileRed].x = 0;
    clips_[kTileRed].y = 0;
    clips_[kTileRed].w = kTileWidth;
    clips_[kTileRed].h = kTileHeight;

    clips_[kTileGreen].x = 0;
    clips_[kTileGreen].y = 32;
    clips_[kTileGreen].w = kTileWidth;
    clips_[kTileGreen].h = kTileHeight;

    clips_[kTileBlue].x = 0;
    clips_[kTileBlue].y = 64;
    clips_[kTileBlue].w = kTileWidth;
    clips_[kTileBlue].h = kTileHeight;

    clips_[kTileTopLeft].x = 32;
    clips_[kTileTopLeft].y = 0;
    clips_[kTileTopLeft].w = kTileWidth;
    clips_[kTileTopLeft].h = kTileHeight;

    clips_[kTileLeft].x = 32;
    clips_[kTileLeft].y = 32;
    clips_[kTileLeft].w = kTileWidth;
    clips_[kTileLeft].h = kTileHeight;

    clips_[kTileBottomLeft].x = 32;
    clips_[kTileBottomLeft].y = 64;
    clips_[kTileBottomLeft].w = kTileWidth;
    clips_[kTileBottomLeft].h = kTileHeight;

    clips_[kTileTop].x = 64;
    clips_[kTileTop].y = 0;
    clips_[kTileTop].w = kTileWidth;
    clips_[kTileTop].h = kTileHeight;

    clips_[kTileCenter].x = 64;
    clips_[kTileCenter].y = 32;
    clips_[kTileCenter].w = kTileWidth;
    clips_[kTileCenter].h = kTileHeight;

    clips_[kTileBottom].x = 64;
    clips_[kTileBottom].y = 64;
    clips_[kTileBottom].w = kTileWidth;
    clips_[kTileBottom].h = kTileHeight;

    clips_[kTileTopRight].x = 96;
    clips_[kTileTopRight].y = 0;
    clips_[kTileTopRight].w = kTileWidth;
    clips_[kTileTopRight].h = kTileHeight;

    clips_[kTileRight].x = 96;
    clips_[kTileRight].y = 32;
    clips_[kTileRight].w = kTileWidth;
    clips_[kTileRight].h =	kTileHeight;

    clips_[kTileBottomRight].x = 96;
    clips_[kTileBottomRight].y = 64;
    clips_[kTileBottomRight].w = kTileWidth;
    clips_[kTileBottomRight].h = kTileHeight;
}

SDL_Rect Tile::box()
{
    SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    return rect;
}

void Tile::render()
{
    if(level_->game()->screen()->camera()->contains(box())) {
        SDL_Rect offset = box();
        level_->game()->screen()->render_texture(level_->texture(), &offset, &clips_[type_]);
    }
}
