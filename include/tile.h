#ifndef TLB_TILE_H_
#define TLB_TILE_H_

#include "SDL2/SDL.h"
#include "point.h"

class Level;
class Tileset;
class Frame;

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
        Tileset * tileset_;

    public:
        Tile();
        Tile(Point point, double width, double height, int type);
        double x_position() const { return x_position_; }
        double y_position() const { return y_position_; }
        double width() const { return width_; }
        double height() const { return height_; }
        int row() const { return row_; }
        int column() const { return column_; }
        int type() const { return type_; }
        Tileset * tileset() const { return tileset_; }

        SDL_Rect box();
        void render(Frame * frame = nullptr);

        void set_width(double width) { width_ = width; }
        void set_height(double height) { height_ = height; }
        void set_tileset(Tileset * tileset) { tileset_ = tileset; }
};

#endif
