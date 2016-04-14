
#include "LevelGraph.h"
#include "LevelNode.h"
#include "Frame.h"
#include "Color.h"
#include "Game.h"
#include "gfx/Renderer.h"

LevelGraph::LevelGraph()
{

}

LevelGraph::~LevelGraph()
{

}

void LevelGraph::addNode(LevelNode * node)
{
    nodes_.push_back(node);
}

void LevelGraph::render(Frame * frame)
{

    // Draw connecting lines
    for(std::list<LevelNode *>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {

        std::list<LevelNode *> adjacent = (*it)->adjacent();

        for(std::list<LevelNode *>::iterator it2 = adjacent.begin(); it2 != adjacent.end(); ++it2) {
            Point start = Point((*it)->position().x() + (*it)->width() / 2, (*it)->position().y() + (*it)->height() / 2);;
            Point end = Point((*it2)->position().x() + (*it2)->width() / 2, (*it2)->position().y() + (*it2)->height() / 2);;
            Game::instance()->renderer()->drawLine(start, end, Color(0, 255, 0));
        }

    }


    // Render each node
    for(std::list<LevelNode *>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {
        (*it)->render(frame);
    }
}
