#ifndef TLB_LEVEL_H_
#define TLB_LEVEL_H_

#include <vector>
#include <string>
#include "SDL2/SDL.h"

class Tile;
class GameObject;
class Camera;
class Game;
class Grid;

class Level
{
    private:
        double width_;
        double height_;
        int total_tiles_;
        std::vector<Tile *> * tiles_;
        Game * game_;
        SDL_Texture * texture_;
        Grid * grid_;

        bool thing;

    public:
        Level(Game * game);

        // accessors
        double width() const { return width_; }
        double height() const { return height_; }
        int total_tiles() const { return total_tiles_; }
        Game * game() const { return game_; }
        SDL_Texture * texture() const { return texture_; }
        std::vector<Tile *> * tiles() const { return tiles_; }
        Grid * grid() const { return grid_; }

        bool load(std::string filename);
        bool touches_wall(GameObject * object, SDL_Rect * rect);

        void render();
        void build_grid();

        bool is_walkable(int row, int col);
};

#endif
