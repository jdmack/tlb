/*
#include <string>
#include <fstream>
#include <cmath>
#include "SDL2/SDL.h"
#include "level_square.h"
#include "game.h"
#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
#include "renderer.h"
#include "tile.h"
#include "utils/logger.h"

LevelSquare::LevelSquare(Game * game)
{
    width_ = 0;
    height_ = 0;
    total_tiles_ = 0;

    game_ = game;
    grid_ = nullptr;

    texture_ = game_->renderer()->load_texture(kAssetArtTiles48);

    tiles_ = new std::vector<Tile *>();

    thing = true;
}


// TODO(2013-09-19/JM): Update the map file standard
bool LevelSquare::load(std::string filename)
{
    Logger::write(Logger::string_stream << "Loading map: " << filename);

    int x = 0;
    int y = 0;

    std::ifstream map(filename.c_str());

    if(map == nullptr) {
        Logger::write(Logger::string_stream << "Failed to open file: " << filename);
        return false;
    }

    game_->renderer()->load_texture(kAssetArtTiles48);

    map >> width_;
        if(map.fail() == true) {
            Logger::write("Failed to read map width from file");
            map.close();
            return false;
        }
    map >> height_;
        if(map.fail() == true) {
            Logger::write("Failed to read map height from file");
            map.close();
            return false;
        }
    map >> total_tiles_;
        if(map.fail() == true) {
            Logger::write("Failed to read total_tiles from file");
            map.close();
            return false;
        }

    // Initialize the tiles
    for(int t = 0; t < total_tiles_; t++) {
        // Determines what kind of tile will be made
        int tile_type = -1;

        // Read tile from map file
        map >> tile_type;

        // If the was a problem in reading the map
        if(map.fail() == true) {
            Logger::write(Logger::string_stream << "Failed to read file | " << t);
            map.close();
            return false;
        }

        // If the number is a valid tile number
        if((tile_type >= 0 ) && (tile_type < kTileSprites)) {
            //tiles_->push_back(new Tile(x, y, tile_type, this));
        }
        else {
            Logger::write("LevelSquare Load: Invalid tile type");
            map.close();
            return false;
        }
        //Logger::write(Logger::string_stream << "Read in tile (" << y / kTileHeight << "," << x / kTileWidth << ") Type: " << tile_type);

        // Move to next tile spot
        x += kTileWidth;

        // If we've gone too far
        if(x >= width_) {
            x = 0;
            y += kTileHeight;
        }
    }

    map.close();
    Logger::write("LevelSquare loaded");
    
    build_grid();

    return true;
}

bool LevelSquare::touches_wall(GameObject * object, SDL_Rect * rect)
{
    // Go through the tiles
    // TODO(2013-09-05/JM): Replace for loop with iterator
    for(int t = 0; t < total_tiles_; t++ ) {

        // If the tile is a wall type tile
        if((tiles_->at(t)->type() >= kTileCenter) && (tiles_->at(t)->type() <= kTileTopLeft ) ) {

            // If the collision box touches the wall tile
            if(object->check_collision(tiles_->at(t)->box()) == true) {
                *rect = tiles_->at(t)->box();
                return true;
            }
        }
    }

    // If no wall tiles were touched
    return false;
}

void LevelSquare::render()
{
    for(std::vector<Tile *>::iterator tile_iterator = tiles_->begin(); tile_iterator != tiles_->end(); ++tile_iterator) {
        (*tile_iterator)->render();
        //if(thing) Logger::write(Logger::string_stream << "Rendering tile: (" << (*tile_iterator)->row() << "," << (*tile_iterator)->column() << ")");
    }
    //if(thing) thing = false;
}

void LevelSquare::build_grid()
{
    Logger::write("Building Grid");
    int rows = (int) std::ceil(height_ / kGridNodeHeight);
    int columns = (int) std::ceil(width_ / kGridNodeWidth);

    grid_ = new Grid(rows, columns);

    for(int r = 0; r < rows ; r++)
        for(int c = 0; c < columns ; c++)
           grid_->node(r, c)->set_walkable(is_walkable(r, c));

    //Logger::write(Logger::string_stream << "Rows:" << rows << ", Columns: " << columns);
}

bool LevelSquare::is_walkable(int row, int col)
{
    int columns = (int) std::ceil(width_ / kGridNodeWidth);

    Tile * this_tile = tiles_->at((columns * row) + col);

    if(this_tile->type() >= 3) {
        //Logger::write(Logger::string_stream << "Returning walkable false: (" << row << "," << col << ") Type: " << this_tile->type());
        //Logger::write(Logger::string_stream << "Recorded: (" << this_tile->row() << "," << this_tile->column() << ")");
        return false;
    }
    //Logger::write(Logger::string_stream << "Returning walkable true: (" << row << "," << col << ") Type: " << this_tile->type());
    //Logger::write(Logger::string_stream << "Recorded: (" << this_tile->row() << "," << this_tile->column() << ")");
    return true;
}
*/
