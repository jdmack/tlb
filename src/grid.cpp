#include "grid.h"
#include "grid_node.h"
#include "point.h"
#include "util/logger.h"

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

    for(int r = 0; r < rows ; r++)
        for(int c = 0; c < columns ; c++)
            nodes_->push_back(new GridNode(r, c));

}

GridNode * Grid::node(int row, int column)
{
    //Logger::write(Logger::ss << "grid: node at (" << row << "," << column << ")");
    return nodes_->at((columns_ * row) + column);
}

void Grid::add_node() 
{
    nodes_->push_back(new GridNode(rows_, columns_++ ));
}

GridNode * Grid::node_at_point(Point point)
{
    bool hex_grid = true;

    int col;
	int row;

	if(hex_grid) {
        // TODO(2014-08-13/JM): Hard coded numbers here for h, s and r
        int x_section = point.x() / (2 * 21);
        int y_section = point.y() / (12 + 24);
        int x_section_pixel = point.x() - x_section * (2 * 21);
        int y_section_pixel = point.y() - y_section * (12 + 24);

        // A section
        if(y_section % 2 == 0) {

            // middle
            row = y_section;
            col = x_section;

            // left
            if(y_section_pixel < (12 - x_section_pixel * 12/21)) {
                row = y_section - 1;
                col = x_section - 1;
            }

            // right
            if(y_section_pixel < (-1 * (12 + x_section_pixel * 12/21))) {
                row = y_section - 1;
                col = x_section;
            }
        }
        else {
            // right
            if(x_section_pixel >= 21) {
                if(y_section_pixel < (2 * 12 - x_section_pixel * 12/21)) {
                    row = y_section - 1;
                    col = x_section - 1;
                }
                else {
                    row = y_section;
                    col = x_section;
                }
            }
            // left
            if(x_section_pixel < 21) {
                if(y_section_pixel < (x_section_pixel * 12/21)) {
                    row = y_section - 1;
                    col = x_section;
                }
                else {
                    row = y_section;
                    col = x_section - 1;
                }
            }
        }
	}
	else {
	    col = point.x() / node_width_;
	    row = point.y() / node_height_;
	}

	//Logger::write(Logger::ss << "Returning node(" << col << "," << row << ")");
	return node(row, col);
}

void Grid::reset_pathfinding()
{
    for(std::vector<GridNode *>::iterator it = nodes_->begin(); it != nodes_->end(); ++it) {
        (*it)->reset();
    }
}

