#include <string>
#include <fstream>
#include "SDL/SDL.h"
#include "level.h"
#include "tile.h"
#include "game_object.h"
#include "screen.h"
#include "game.h"
#include "util/logger.h"

Level::Level(Game * game)
{
    width_ = 0;
    height_ = 0;
    total_tiles_ = 0;

    game_ = game;

    texture_ = game_->screen()->load_texture(kAssetArtTiles);

    tiles_ = new std::vector<Tile *>();
}

bool Level::load(std::string filename)
{
    Logger::write(Logger::string_stream << "Loading map: " << filename);

    int x = 0;
    int y = 0;

    std::ifstream map(filename);

    if(map == nullptr) {
        Logger::write(Logger::string_stream << "Failed to open file: " << filename);
        return false;
    }

    game_->screen()->load_texture(kAssetArtTiles);

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
            tiles_->push_back(new Tile(x, y, tile_type, this));
        }
        else {
            Logger::write("Level Load: Invalid tile type");
            map.close();
            return false;
        }

        // Move to next tile spot
        x += kTileWidth;

        // If we've gone too far
        if(x >= width_) {
            x = 0;
            y += kTileHeight;
        }
    }

    map.close();
    return true;
}

bool Level::touches_wall(GameObject * object, SDL_Rect * rect)
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

void Level::render()
{
    for(std::vector<Tile *>::iterator tile_iterator = tiles_->begin(); tile_iterator != tiles_->end(); ++tile_iterator) {
        (*tile_iterator)->render();
    }
}
