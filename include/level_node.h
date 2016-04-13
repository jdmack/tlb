#ifndef TLB_LEVEL_NODE_H_
#define TLB_LEVEL_NODE_H_

#include <string>
#include <list>
#include "point.h"

class Graphic;
class Frame;

class LevelNode
{
    private:
        Point position_;
        int width_;
        int height_;

        std::list<LevelNode *> adjacent_;
        std::string levelFile_;

        Graphic * graphic_;

    public:
        LevelNode();
        ~LevelNode();

        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        std::list<LevelNode *> adjacent() const { return adjacent_; }

        void setPosition(Point position) { position_ = position; }
        void setWidth(int width) { width_ = width; }
        void setHeight(int height) { height_ = height; }
        void setLevelFile(std::string levelFile) { levelFile_ = levelFile; }
        void setGraphic(Graphic * graphic) { graphic_ = graphic; }

        void addAdjacent(LevelNode * node);
        void render(Frame * frame = nullptr);

};

#endif
