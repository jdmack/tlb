#ifndef TLB_TILE_H_
#define TLB_TILE_H_

#include "SDL2/SDL.h"

//const double kTileWidth = 42;
const double kTileWidth = 48;
const double kTileHeight = 48;
const int kTileSprites = 12;

const int kTileRed         = 0;
const int kTileGreen       = 1;
const int kTileBlue        = 2;
const int kTileCenter      = 3;
const int kTileTop         = 4;
const int kTileTopRight    = 5;
const int kTileRight       = 6;
const int kTileBottomRight = 7;
const int kTileBottom      = 8;
const int kTileBottomLeft  = 9;
const int kTileLeft        = 10;
const int kTileTopLeft     = 11;

class Level;

class Tile
{
    private:
        double x_position_;
        double y_position_;
        double width_;
        double height_;
        int row_;
        int column_;
        int type_;
        Level * level_;
        SDL_Rect clips_[kTileSprites];

    public:
        Tile();
        Tile(double x, double y, int type, Level * level);
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double width() const { return width_; }
        double height() const { return height_; }
        int row() const { return row_; }
        int column() const { return column_; }
        int type() const { return type_; }
        SDL_Rect box();
        void render();
};

#endif
