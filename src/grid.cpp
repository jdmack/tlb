#include "grid.h"
#include "grid_node.h"
#include "point.h"
#include "utils/logger.h"

Grid::Grid()
{
    rows_    = 0;
    columns_ = 0;
    node_width_ = kGridNodeWidth;
    node_height_ = kGridNodeWidth;

    nodes_ = new std::vector<GridNode *>();
}

Grid::Grid(int rows, int columns)
{
    rows_    = rows;
    columns_ = columns;
    node_width_ = kGridNodeWidth;
    node_height_ = kGridNodeWidth;

    nodes_ = new std::vector<GridNode *>();

    int row = 0;
    int col = 0;

    for(int i = 0; i < rows * columns; i++) {
        nodes_->push_back(new GridNode(row, col));
        col++;
        if(col >= columns_) {
            col -= columns_;
            row++;
        }
    }
}

GridNode * Grid::node(int row, int column)
{
    //Logger::write(Logger::string_stream << "grid: node at (" << row << "," << column << ")");
    return nodes_->at((columns_ * row) + column);
}

void Grid::add_node() 
{
    nodes_->push_back(new GridNode(rows_, columns_++ ));
}

GridNode * Grid::node_at_point(Point point)
{
    int col = point.x() / node_width_;
	int row = point.y() / node_height_;

	Logger::write(Logger::string_stream << "return node: (" << row << "," << col << ")");

	return node(row, col);
}
