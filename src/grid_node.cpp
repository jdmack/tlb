
#include "grid_node.h"
#include "point.h"

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
    return Point(((column_ * width_) + (width_ / 2)), ((row_ * height_) + (height_ / 2)));
}
