#ifndef TLB_PATHFINDER_H_
#define TLB_PATHFINDER_H_

#include <list>

class Grid;
class GridNode;

class Pathfinder
{
    private:

    public:
        // constructors
        Pathfinder();
        virtual ~Pathfinder();


        virtual std::list<GridNode *> * run(GridNode * startNode, GridNode * endNode);

};
#endif

