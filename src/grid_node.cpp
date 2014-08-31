
#include <sstream>

#include "grid_node.h"
#include "point.h"
#include "util/logger.h"

GridNode::GridNode()
{
    row_     = 0;
    column_  = 0;
    width_   = kGridNodeWidth;
    height_  = kGridNodeHeight;
    f_score_ = 0;
    g_score_ = 0;
    h_score_ = 0;

    walkable_ = true;
    parent_   = nullptr;
}

GridNode::GridNode(int row, int column)
{
    row_     = row;
    column_  = column;
    width_   = kGridNodeWidth;
    height_  = kGridNodeHeight;
    f_score_ = 0;
    g_score_ = 0;
    h_score_ = 0;

    walkable_ = true;
    parent_   = nullptr;
}

void GridNode::set_scores(int f_score, int g_score, int h_score)
{
    f_score_ = f_score;
    g_score_ = g_score;
    h_score_ = h_score;
}

int GridNode::compare(GridNode * node)
{
    if(f_score_ > node->f_score()) {
        return 1;
    }
    else if(f_score_ > node->f_score()) {
        return -1;
    }
    else {
        return 0;
    }
}

Point GridNode::center_point()
{
    bool hex_grid = true;

    int x;
    int y;
    if(hex_grid) {
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
    set_scores(0,0,0);
    parent_ = nullptr;
}

bool GridNode::operator>(const GridNode &other) const {

    if(f_score_ > other.f_score()) {
        return true;
    }
    else {
        return false;
    }
}

std::string GridNode::to_string()
{
    std::stringstream ss;
    ss << "GridNode(" << column_ << "," << row_ << ")";
    return ss.str();
}
