#ifndef TLB_PATHFINDER_HEX_H_
#define TLB_PATHFINDER_HEX_H_

#include <list>
#include <string>
#include "pathfinder.h"

const int kNodeCostAdj = 10;

class Grid;
class GridNode;

class PathfinderHex : public Pathfinder
{
    private:
        Grid * grid_;
        std::list<GridNode *> open_list;
        std::list<GridNode *> closed_list;

        bool is_walkable(int row, int col);

    public:
        // constructors
        PathfinderHex(Grid * grid);

        // accessors
        Grid * grid() const { return grid_; }

        // mutators
        void set_grid(Grid * grid) { grid_ = grid; }

        std::list<GridNode *> * run(GridNode * start_node, GridNode * end_node);
        void reset();

        // list
        bool open_list_contains(GridNode * node);
        bool closed_list_contains(GridNode * node);

        std::string open_list_to_string();
        //void closed_list_to_string();

        int calculate_h(GridNode * start, GridNode * end);

};
#endif

