#include "tile.h"
#include "level.h"
#include "camera.h"
#include "renderer.h"
#include "game.h"

Tile::Tile()
{
    x_position_ = 0;
    y_position_ = 0;
    width_ = kTileWidth;
    height_ = kTileHeight;
    type_ = 0;
    level_ = nullptr;

    row_ = -1;
    column_ = -1;
}

Tile::Tile(double x, double y, int type, Level * level)
{
    x_position_ = x;
    y_position_ = y;
    width_ = kTileWidth;
    height_ = kTileHeight;
    type_ = type;

    row_ = y_position_ / kTileHeight;
    column_ = x_position_ / kTileWidth;

    level_ = level;

    clips_[kTileRed].x = 0 * width_;
    clips_[kTileRed].y = 0 * height_;
    clips_[kTileRed].w = width_;
    clips_[kTileRed].h = height_;

    clips_[kTileGreen].x = 0 * width_;
    clips_[kTileGreen].y = 1 * height_;
    clips_[kTileGreen].w = width_;
    clips_[kTileGreen].h = height_;

    clips_[kTileBlue].x = 0 * width_;
    clips_[kTileBlue].y = 2 * height_;
    clips_[kTileBlue].w = width_;
    clips_[kTileBlue].h = height_;

    clips_[kTileTopLeft].x = 1 * width_;
    clips_[kTileTopLeft].y = 0 * height_;
    clips_[kTileTopLeft].w = width_;
    clips_[kTileTopLeft].h = height_;

    clips_[kTileLeft].x = 1 * width_;
    clips_[kTileLeft].y = 1 * height_;
    clips_[kTileLeft].w = width_;
    clips_[kTileLeft].h = height_;

    clips_[kTileBottomLeft].x = 1 * width_;
    clips_[kTileBottomLeft].y = 2 * height_;
    clips_[kTileBottomLeft].w = width_;
    clips_[kTileBottomLeft].h = height_;

    clips_[kTileTop].x = 2 * width_;
    clips_[kTileTop].y = 0 * height_;
    clips_[kTileTop].w = width_;
    clips_[kTileTop].h = height_;

    clips_[kTileCenter].x = 2 * width_;
    clips_[kTileCenter].y = 1 * height_;
    clips_[kTileCenter].w = width_;
    clips_[kTileCenter].h = height_;

    clips_[kTileBottom].x = 2 * width_;
    clips_[kTileBottom].y = 2 * height_;
    clips_[kTileBottom].w = width_;
    clips_[kTileBottom].h = height_;

    clips_[kTileTopRight].x = 3 * width_;
    clips_[kTileTopRight].y = 0 * height_;
    clips_[kTileTopRight].w = width_;
    clips_[kTileTopRight].h = height_;

    clips_[kTileRight].x = 3 * width_;
    clips_[kTileRight].y = 1 * height_;
    clips_[kTileRight].w = width_;
    clips_[kTileRight].h =	height_;

    clips_[kTileBottomRight].x = 3 * width_;
    clips_[kTileBottomRight].y = 2 * height_;
    clips_[kTileBottomRight].w = width_;
    clips_[kTileBottomRight].h = height_;
}

SDL_Rect Tile::box()
{
    SDL_Rect rect = { (int)x_position_, (int)y_position_, (int)width_, (int)height_ };
    return rect;
}

void Tile::render()
{
    if(level_->game()->renderer()->camera()->contains(box())) {
        SDL_Rect offset = box();
        level_->game()->renderer()->render_texture(level_->texture(), &offset, &clips_[type_]);
    }
}
