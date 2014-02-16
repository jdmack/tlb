#ifndef TLB_GRID_H_
#define TLB_GRID_H_

#include <vector>

class GridNode;
class Point;
class Level;

class Grid
{
    private:
        int rows_;
        int columns_;
        int node_width_;
        int node_height_;
        Level * level_;

        std::vector<GridNode *> * nodes_;

    public:
        // constructors
        Grid();
        Grid(int rows, int columns, Level * level);

        // accessors
        int rows() const { return rows_; }
        int columns() const { return columns_; }
        std::vector<GridNode *> * nodes() const { return nodes_; }

        // mutators
        void rows(int rows) { rows_ = rows; }
        void columns(int columns) { columns_ = columns; }

        GridNode * node(int row, int column);
        void add_node();
        GridNode * node_at_point(Point point);
        void reset_pathfinding();
};

#endif

