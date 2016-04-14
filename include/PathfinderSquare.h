#ifndef TLB_PATHFINDER_SQUARE_H_
#define TLB_PATHFINDER_SQUARE_H_

#include <list>
#include <string>
#include "Pathfinder.h"

const int kNodeCostHor = 10;
const int kNodeCostVer = 10;
const int kNodeCostDia = 14;

class Grid;
class GridNode;

class PathfinderSquare : public Pathfinder
{
    private:
        Grid * grid_;
        std::list<GridNode *> openList;
        std::list<GridNode *> closedList;

        bool isWalkable(int row, int col);

    public:
        // constructors
        PathfinderSquare(Grid * grid);

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
