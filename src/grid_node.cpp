
#include "grid_node.h"

GridNode::GridNode()
{
    row_     = 0;
    column_  = 0;
    f_score_ = 0;
    g_score_ = 0;
    h_score_ = 0;
}

GridNode::GridNode(int row, int column)
{
    row_     = row;
    column_  = column;
    f_score_ = 0;
    g_score_ = 0;
    h_score_ = 0;
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
