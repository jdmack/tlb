#ifndef TLB_LEVEL_H_
#define TLB_LEVEL_H_

#include <vector>
#include <string>
#include "SDL2/SDL.h"


class Tile;
class GameObject;
class Camera;
class Grid;
class Tileset;
class Frame;

class Level
{
    private:
        double width_;
        double height_;
        double rows_;
        double columns_;
        double tile_width_;
        double tile_height_;
        int total_tiles_;
        std::vector<Tile *> * tiles_;
        Grid * grid_;
        Tileset * tileset_;

        bool thing;

    public:
        Level();

        // accessors
        double width() const { return width_; }
        double height() const { return height_; }
        int total_tiles() const { return total_tiles_; }
        std::vector<Tile *> * tiles() const { return tiles_; }
        Grid * grid() const { return grid_; }

        bool load(std::string filename);
        bool touches_wall(GameObject * object, SDL_Rect * rect);

        void render(Frame * frame = nullptr);
        void build_grid();

        bool is_walkable(int row, int col);
};

#endif
