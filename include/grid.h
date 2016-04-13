#ifndef TLB_GRID_H_
#define TLB_GRID_H_

#include <vector>

class GridNode;
class Point;

class Grid
{
    private:
        int rows_;
        int columns_;
        int nodeWidth_;
        int nodeHeight_;

        std::vector<GridNode *> * nodes_;

    public:
        // constructors
        Grid();
        Grid(int rows, int columns);

        // accessors
        int rows() const { return rows_; }
        int columns() const { return columns_; }
        std::vector<GridNode *> * nodes() const { return nodes_; }

        // mutators
        void rows(int rows) { rows_ = rows; }
        void columns(int columns) { columns_ = columns; }

        GridNode * node(int row, int column);
        void addNode();
        GridNode * nodeAtPoint(Point point);
        void resetPathfinding();
};

#endif

