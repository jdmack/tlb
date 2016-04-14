
#include <sstream>

#include "GridNode.h"
#include "Point.h"
#include "util/Logger.h"

GridNode::GridNode()
{
    row_     = 0;
    column_  = 0;
    width_   = kGridNodeWidth;
    height_  = kGridNodeHeight;
    fScore_ = 0;
    gScore_ = 0;
    hScore_ = 0;

    walkable_ = true;
    parent_   = nullptr;
}

GridNode::GridNode(int row, int column)
{
    row_     = row;
    column_  = column;
    width_   = kGridNodeWidth;
    height_  = kGridNodeHeight;
    fScore_ = 0;
    gScore_ = 0;
    hScore_ = 0;

    walkable_ = true;
    parent_   = nullptr;
}

void GridNode::setScores(int fScore, int gScore, int hScore)
{
    fScore_ = fScore;
    gScore_ = gScore;
    hScore_ = hScore;
}

int GridNode::compare(GridNode * node)
{
    if(fScore_ > node->fScore()) {
        return 1;
    }
    else if(fScore_ > node->fScore()) {
        return -1;
    }
    else {
        return 0;
    }
}

Point GridNode::centerPoint()
{
    bool hexGrid = false;

    int x;
    int y;
    if(hexGrid) {
        int width = 42;
        int height = 48;
        int radius = 21;
        int side = 24;
        int h = 12;

        if(row_ % 2 == 0) {
            x = column_ * 2 * radius;
            y = row_ * (h + side);
        }
        else {
            x = column_ * (2 * radius) + radius;
            y = row_ * (h + side);
        }

        x += (width / 2);
        y += (height / 2);
    }
    else {
        x = (column_ * width_) + (width_ / 2);
        y = (row_ * height_) + (height_ / 2);
    }

    // Square grid center point code

    //Logger::write(Logger::ss << "Center Point of GridNode(" << column_ << "," << row_ <<"):(" << x << ", " << y << ")");

    return Point(x, y);
}

void GridNode::reset()
{
    setScores(0,0,0);
    parent_ = nullptr;
}

bool GridNode::operator>(const GridNode &other) const {

    if(fScore_ > other.fScore()) {
        return true;
    }
    else {
        return false;
    }
}

std::string GridNode::toString()
{
    std::stringstream ss;
    ss << "GridNode(" << column_ << "," << row_ << ")";
    return ss.str();
}
