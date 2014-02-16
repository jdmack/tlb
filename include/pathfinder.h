#ifndef TLB_PATHFINDER_H_
#define TLB_PATHFINDER_H_

#include <list>
#include <string>

const int kNodeCostHor = 10;
const int kNodeCostVer = kNodeCostHor;
const int kNodeCostDia = 14;

class Level;
class GridNode;

class Pathfinder
{
    private:
        Level * level_;
        std::list<GridNode *> open_list;
        std::list<GridNode *> closed_list;

    public:
        // constructors
        Pathfinder(Level * level);

        // accessors
        Level * level() const { return level_; }

        // mutators
        void set_level(Level * level) { level_ = level; }

        std::list<GridNode *> * run(GridNode * start_node, GridNode * end_node);
        void reset();

        // list
        bool open_list_contains(GridNode * node);
        bool closed_list_contains(GridNode * node);

        std::string open_list_to_string();
        //void closed_list_to_string();

};
#endif

