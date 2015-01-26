#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SDL2/SDL.h"
#include "level.h"
#include "game.h"
#include "game_object.h"
#include "grid.h"
#include "grid_node.h"
#include "renderer.h"
#include "frame.h"
#include "tile.h"
#include "tileset.h"
#include "util/logger.h"
#include "util/math.h"
#include "rapidxml/rapidxml.hpp"


Level::Level()
{
    width_ = 0;
    height_ = 0;
    total_tiles_ = 0;

    grid_ = nullptr;

    tiles_ = new std::vector<Tile *>();

    thing = true;
    tileset_ = nullptr;
}


// TODO(2013-09-19/JM): Update the map file standard
bool Level::load(std::string filename)
{
    Logger::write(Logger::ss << "Loading map: " << filename);

    // open xml doc
    rapidxml::xml_document<> doc;

    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string content(buffer.str());
    doc.parse<0>(&content[0]);

    rapidxml::xml_node<> * level = doc.first_node();                // this is the level element

    rapidxml::xml_node<> * tiles = level->first_node("tiles");      // this is the tiles element

    std::string tileset = tiles->first_attribute("tileset")->value();
    tileset_ = new Tileset(tileset);


    columns_ = std::atoi(tiles->first_attribute("columns")->value());
    rows_ = std::atoi(tiles->first_attribute("rows")->value());
    tile_width_ = std::atoi(tiles->first_attribute("width")->value());
    tile_height_ = std::atoi(tiles->first_attribute("height")->value());

    width_ = rows_ * tile_width_;
    height_ = columns_ * tile_height_;

    int row = 0;
    int column = 0;

    // Iterate through tiles
    for(rapidxml::xml_node<> * tile = tiles->first_node("tile"); tile; tile = tile->next_sibling()) {

        int tile_type = std::atoi(tile->first_attribute("type")->value());

        int x = std::atoi(tile->first_attribute("x")->value());
        int y = std::atoi(tile->first_attribute("y")->value());


        // If the number is a valid tile number
        //if((tile_type >= 0 ) && (tile_type < kTileSprites)) {
        Tile * new_tile = new Tile(Point(x, y), tile_width_, tile_height_, tile_type);
        new_tile->set_tileset(tileset_);
        tiles_->push_back(new_tile);
        //}
        //else {
            //Logger::write("Level Load: Invalid tile type");
            //return false;
        //}
        //Logger::write(Logger::ss << "Read in tile (" << x << "," << y << ") Type: " << tile_type);

        column++;
        if(column >= columns_) {
            column = 0;
            row++;
        }

    }

    Logger::write("Level loaded");
    
    build_grid();

    return true;
}

bool Level::touches_wall(GameObject * object, SDL_Rect * rect)
{
    /*
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
*/
    // If no wall tiles were touched
    return false;
}

void Level::render(Frame * frame)
{
    for(std::vector<Tile *>::iterator tile_iterator = tiles_->begin(); tile_iterator != tiles_->end(); ++tile_iterator) {
        (*tile_iterator)->render(frame);
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




        // For HEX
        /*
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
        */

