#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SDL2/SDL.h"
#include "Level.h"
#include "Game.h"
#include "GameObject.h"
#include "Grid.h"
#include "GridNode.h"
#include "gfx/Renderer.h"
#include "Frame.h"
#include "gfx/Tile.h"
#include "gfx/Tileset.h"
#include "util/Logger.h"
#include "math/Math.h"
#include "rapidxml/rapidxml.hpp"


Level::Level()
{
    width_ = 0;
    height_ = 0;
    totalTiles_ = 0;

    grid_ = nullptr;

    tiles_ = new std::vector<Tile *>();

    thing = true;
    tileset_ = nullptr;

    rows_ = 0;
    columns_ = 0;

    tileWidth_= 0;
    tileHeight_ = 0;
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
    tileWidth_ = std::atoi(tiles->first_attribute("width")->value());
    tileHeight_ = std::atoi(tiles->first_attribute("height")->value());

    width_ = rows_ * tileWidth_;
    height_ = columns_ * tileHeight_;

    int row = 0;
    int column = 0;

    // Iterate through tiles
    for(rapidxml::xml_node<> * tile = tiles->first_node("tile"); tile; tile = tile->next_sibling()) {

        int tileType = std::atoi(tile->first_attribute("type")->value());

        int x = std::atoi(tile->first_attribute("x")->value());
        int y = std::atoi(tile->first_attribute("y")->value());


        // If the number is a valid tile number
        //if((tileType >= 0 ) && (tileType < kTileSprites)) {
        Tile * newTile = new Tile(Point(x, y), tileWidth_, tileHeight_, tileType);
        newTile->setTileset(tileset_);
        tiles_->push_back(newTile);
        //}
        //else {
            //Logger::write("Level Load: Invalid tile type");
            //return false;
        //}
        //Logger::write(Logger::ss << "Read in tile (" << x << "," << y << ") Type: " << tileType);

        column++;
        if(column >= columns_) {
            column = 0;
            row++;
        }

    }

    Logger::write("Level loaded");
    
    buildGrid();

    return true;
}

bool Level::touchesWall(GameObject * object, SDL_Rect * rect)
{
    /*
    // Go through the tiles
    // TODO(2013-09-05/JM): Replace for loop with iterator
    for(int t = 0; t < totalTiles_; t++ ) {

        // If the tile is a wall type tile
        if((tiles_->at(t)->type() >= kTileCenter) && (tiles_->at(t)->type() <= kTileTopLeft ) ) {

            // If the collision box touches the wall tile
            if(object->checkCollision(tiles_->at(t)->box()) == true) {
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
    for(std::vector<Tile *>::iterator tileIterator = tiles_->begin(); tileIterator != tiles_->end(); ++tileIterator) {
        (*tileIterator)->render(frame);
        //if(thing) Logger::write(Logger::ss << "Rendering tile: (" << (*tileIterator)->row() << "," << (*tileIterator)->column() << ")");
    }
    //if(thing) thing = false;
}

void Level::buildGrid()
{
    Logger::write("Building Grid");

    grid_ = new Grid(rows_, columns_);

    for(int r = 0; r < rows_ ; r++)
        for(int c = 0; c < columns_ ; c++)
           grid_->node(r, c)->setWalkable(isWalkable(r, c));

    //Logger::write(Logger::ss << "Rows:" << rows_ << ", Columns: " << columns_);
}

bool Level::isWalkable(int row, int col)
{
    Tile * thisTile = tiles_->at((columns_ * row) + col);

    if(thisTile->type() >= 3) {
        //Logger::write(Logger::ss << "Returning walkable false: (" << col << "," << row << ") Type: " << thisTile->type());
        //Logger::write(Logger::ss << "Recorded: (" << thisTile->row() << "," << thisTile->column() << ")");
        return false;
    }
    //Logger::write(Logger::ss << "Returning walkable true: (" << col << "," << row << ") Type: " << thisTile->type());
    //Logger::write(Logger::ss << "Recorded: (" << thisTile->row() << "," << thisTile->column() << ")");
    return true;
}




        // For HEX
        /*
        if(hexGrid) {
            x = tileWidth_ * column;
            // Shift tiles left to cover white space
            x -= tileWidth_ / 2;

            if((row % 2) == 1) {
                x += tileWidth_ / 2;
            }
            // TODO(2014-08-13/JM): 12 is "h" part of hexagon, replace with actual calculation of value from map file
            y = (tileHeight_ - 12) * row;
            // Shift tiles up to cover white space
            y -= tileHeight_ - 12;
        }
        */

