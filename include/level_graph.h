#ifndef TLB_LEVEL_GRAPH_H_
#define TLB_LEVEL_GRAPH_H_

#include <list>

class LevelNode;

class LevelGraph
{

    private:
        std::list<LevelNode *> nodes_;

    public:
        LevelGraph();
        ~LevelGraph();

        void add_node(LevelNode * node);



};

#endif
