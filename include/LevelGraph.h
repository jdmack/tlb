#ifndef TLB_LEVEL_GRAPH_H_
#define TLB_LEVEL_GRAPH_H_

#include <list>

class LevelNode;
class Frame;

class LevelGraph
{

    private:
        std::list<LevelNode *> nodes_;

    public:
        LevelGraph();
        ~LevelGraph();

        void addNode(LevelNode * node);
        void render(Frame * frame = nullptr);





};

#endif
