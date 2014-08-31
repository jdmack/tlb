#include <string>
#include <fstream>
#include <cmath>
#include "SDL2/SDL.h"
#include "level.h"
#include "game.h"
#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
#include "renderer.h"
#include "tile.h"
#include "util/logger.h"
#include "util/math.h"

Level::Level(Game * game)
{
    width_ = 0;
    height_ = 0;
    total_tiles_ = 0;

    game_ = game;
    grid_ = nullptr;

    //texture_ = game_->renderer()->load_texture(kAssetArtTilesHexIsometric);
    texture_ = game_->renderer()->load_texture(kAssetArtTilesHexagon);

    tiles_ = new std::vector<Tile *>();

    thing = true;
}


// TODO(2013-09-19/JM): Update the map file standard
bool Level::load(std::string filename)
{
    //Point p1 = Point (48, 48);
    //Point p2 = Point (96, 48);

    //p1 = Math::convert_to_isometric(p1);
    //p2 = Math::convert_to_isometric(p2);
    //p1 = Math::convert_to_cartesian(p1);
    //p2 = Math::convert_to_cartesian(p2);
    //double distance = p1.distance_from(p2);
    //Logger::write(Logger::ss << "Distance: " << distance);

    bool hex_grid = true;
    Logger::write(Logger::ss << "Loading map: " << filename);

    std::ifstream map(filename.c_str());

    if(map == nullptr) {
        Logger::write(Logger::ss << "Failed to open file: " << filename);
        return false;
    }

    map >> total_tiles_;
    if(map.fail() == true) {
        Logger::write("Failed to read total_tiles from file");
        map.close();
        return false;
    }
    map >> columns_;
    if(map.fail() == true) {
        Logger::write("Failed to read map columns from file");
        map.close();
        return false;
    }
    map >> rows_;
    if(map.fail() == true) {
        Logger::write("Failed to read map rows from file");
        map.close();
        return false;
    }
    map >> tile_width_;
    if(map.fail() == true) {
        Logger::write("Failed to read map tile_width from file");
        map.close();
        return false;
    }
    map >> tile_height_;
    //tile_height_ = tile_height_ * 2 / 3;
    if(map.fail() == true) {
        Logger::write("Failed to read map tile_height from file");
        map.close();
        return false;
    }
    width_ = rows_ * tile_width_;
    //height_ = columns_ * tile_height_;
    height_ = columns_ * tile_height_ / 2;

    int row = 0;
    int column = 0;

    // Initialize the tiles
    for(int t = 0; t < total_tiles_; t++) {

        // Determines what kind of tile will be made
        int tile_type = -1;

        // Read tile from map file
        map >> tile_type;

        // If the was a problem in reading the map
        if(map.fail() == true) {
            Logger::write(Logger::ss << "Failed to read file | " << t);
            map.close();
            return false;
        }

        int x;
        int y;

        if(hex_grid) {
            x = tile_width_ * column;
            // Shift tiles left to cover white space
            x -= tile_width_ / 2;

            if((row % 2) == 1) {
                x += tile_width_ / 2;
            }
            // TODO(2014-08-13/JM): 12 is "h" part of hexagon, replace with actual calculation of value from map file
            y = (tile_height_ - 12) * row;
            // Shift tiles up to cover white space
            y -= tile_height_ - 12;
        }
        else {
            x = tile_width_ * column / 2;
            y = tile_height_ * row;
        }

        // If the number is a valid tile number
        if((tile_type >= 0 ) && (tile_type < kTileSprites)) {
            tiles_->push_back(new Tile(Point(x, y), tile_width_, tile_height_, tile_type, this));
        }
        else {
            Logger::write("Level Load: Invalid tile type");
            map.close();
            return false;
        }
        //Logger::write(Logger::ss << "Read in tile (" << y / kTileHeight << "," << x / kTileWidth << ") Type: " << tile_type);

        column++;
        if(column >= columns_) {
            column = 0;
            row++;
        }

    }

    map.close();
    Logger::write("Level loaded");
    
    build_grid();

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
        //if(thing) Logger::write(Logger::ss << "Rendering tile: (" << (*tile_iterator)->row() << "," << (*tile_iterator)->column() << ")");
    }
    //if(thing) thing = false;
}

void Level::build_grid()
{
    Logger::write("Building Grid");

    grid_ = new Grid(rows_, columns_);

    for(int r = 0; r < rows_ ; r++)
        for(int c = 0; c < columns_ ; c++)
           grid_->node(r, c)->set_walkable(is_walkable(r, c));

    //Logger::write(Logger::ss << "Rows:" << rows_ << ", Columns: " << columns_);
}

bool Level::is_walkable(int row, int col)
{
    Tile * this_tile = tiles_->at((columns_ * row) + col);

    if(this_tile->type() >= 3) {
        //Logger::write(Logger::ss << "Returning walkable false: (" << col << "," << row << ") Type: " << this_tile->type());
        //Logger::write(Logger::ss << "Recorded: (" << this_tile->row() << "," << this_tile->column() << ")");
        return false;
    }
    //Logger::write(Logger::ss << "Returning walkable true: (" << col << "," << row << ") Type: " << this_tile->type());
    //Logger::write(Logger::ss << "Recorded: (" << this_tile->row() << "," << this_tile->column() << ")");
    return true;
}
