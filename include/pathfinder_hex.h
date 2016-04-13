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
        std::list<GridNode *> openList;
        std::list<GridNode *> closedList;

        bool isWalkable(int row, int col);

    public:
        // constructors
        PathfinderHex(Grid * grid);

        // accessors
        Grid * grid() const { return grid_; }

        // mutators
        void setGrid(Grid * grid) { grid_ = grid; }

        std::list<GridNode *> * run(GridNode * startNode, GridNode * endNode);
        void reset();

        // list
        bool openListContains(GridNode * node);
        bool closedListContains(GridNode * node);

        std::string openListToString();
        //void closedListToString();

        int calculateH(GridNode * start, GridNode * end);

};
#endif

