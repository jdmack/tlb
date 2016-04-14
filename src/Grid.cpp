#include "Grid.h"
#include "GridNode.h"
#include "Point.h"
#include "util/Logger.h"

Grid::Grid()
{
    rows_    = 0;
    columns_ = 0;
    nodeWidth_ = kGridNodeWidth;
    nodeHeight_ = kGridNodeWidth;

    nodes_ = new std::vector<GridNode *>();
}

Grid::Grid(int rows, int columns)
{
    rows_    = rows;
    columns_ = columns;
    nodeWidth_ = kGridNodeWidth;
    nodeHeight_ = kGridNodeWidth;

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

void Grid::addNode() 
{
    nodes_->push_back(new GridNode(rows_, columns_++ ));
}

GridNode * Grid::nodeAtPoint(Point point)
{
    bool hexGrid = false;

    int col;
	int row;

	if(hexGrid) {
        // TODO(2014-08-13/JM): Hard coded numbers here for h, s and r
        int xSection = point.x() / (2 * 21);
        int ySection = point.y() / (12 + 24);
        int xSectionPixel = point.x() - xSection * (2 * 21);
        int ySectionPixel = point.y() - ySection * (12 + 24);

        // A section
        if(ySection % 2 == 0) {

            // middle
            row = ySection;
            col = xSection;

            // left
            if(ySectionPixel < (12 - xSectionPixel * 12/21)) {
                row = ySection - 1;
                col = xSection - 1;
            }

            // right
            if(ySectionPixel < (-1 * (12 + xSectionPixel * 12/21))) {
                row = ySection - 1;
                col = xSection;
            }
        }
        else {
            // right
            if(xSectionPixel >= 21) {
                if(ySectionPixel < (2 * 12 - xSectionPixel * 12/21)) {
                    row = ySection - 1;
                    col = xSection - 1;
                }
                else {
                    row = ySection;
                    col = xSection;
                }
            }
            // left
            if(xSectionPixel < 21) {
                if(ySectionPixel < (xSectionPixel * 12/21)) {
                    row = ySection - 1;
                    col = xSection;
                }
                else {
                    row = ySection;
                    col = xSection - 1;
                }
            }
        }
	}
	else {
	    col = point.x() / nodeWidth_;
	    row = point.y() / nodeHeight_;
	}

	//Logger::write(Logger::ss << "Returning node(" << col << "," << row << ")");
	return node(row, col);
}

void Grid::resetPathfinding()
{
    for(std::vector<GridNode *>::iterator it = nodes_->begin(); it != nodes_->end(); ++it) {
        (*it)->reset();
    }
}

