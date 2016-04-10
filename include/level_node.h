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
        std::string level_file_;

        Graphic * graphic_;

    public:
        LevelNode();
        ~LevelNode();

        Point position() const { return position_; }
        int width() const { return width_; }
        int height() const { return height_; }
        std::list<LevelNode *> adjacent() const { return adjacent_; }

        void set_position(Point position) { position_ = position; }
        void set_width(int width) { width_ = width; }
        void set_height(int height) { height_ = height; }
        void set_level_file(std::string level_file) { level_file_ = level_file; }
        void set_graphic(Graphic * graphic) { graphic_ = graphic; }

        void add_adjacent(LevelNode * node);
        void render(Frame * frame = nullptr);

};

#endif