#include "gfx/Tileset.h"
#include "gfx/Renderer.h"
#include "Game.h"
#include "Point.h"
#include "rapidxml/rapidxml.hpp"
#include "util/Logger.h"


Tileset::Tileset()
{
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;
}

Tileset::Tileset(std::string filename)
{
    width_ = 0;
    height_ = 0;

    texture_ = nullptr;

    load(filename);
}

bool Tileset::load(std::string filename)
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

    rapidxml::xml_node<> * tileset = doc.first_node();

    std::string assetFilename = tileset->first_attribute("asset")->value();
    texture_ = Game::instance()->renderer()->loadTexture(assetFilename);

    // Iterate through tiles
    for(rapidxml::xml_node<> * tile = tileset->first_node("tile"); tile; tile = tile->next_sibling()) {

        int type = std::atoi(tile->first_attribute("type")->value());
        int x = std::atoi(tile->first_attribute("x")->value());
        int y = std::atoi(tile->first_attribute("y")->value());
        int width = std::atoi(tile->first_attribute("width")->value());
        int height = std::atoi(tile->first_attribute("height")->value());

        SDL_Rect rect = { x, y, width, height };

        clips_.insert(std::pair<int, SDL_Rect>(type, rect));
    }
    return true;
}
