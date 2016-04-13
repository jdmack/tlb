#ifndef TLB_GRID_NODE_H_
#define TLB_GRID_NODE_H_

#include <string>

const int kGridNodeWidth  = 48;
const int kGridNodeHeight = 48;
//const int kGridNodeWidth  = 24;
//const int kGridNodeHeight = 24;


class Point;

class GridNode
{
    // TODO(2013-09-11/JM): Remove the scores to a different object
    // to keep the pathfinding algorithm separate
    private:
        int row_;
        int column_;
        double width_;
        double height_;
        int fScore_;
        int gScore_;
        int hScore_;
        bool walkable_;

        GridNode * parent_;

    public:
        // constructors
        GridNode();
        GridNode(int row, int column);

        // accessors
        int row() const { return row_; }
        int column() const { return column_; }
        int fScore() const { return fScore_; }
        int gScore() const { return gScore_; }
        int hScore() const { return hScore_; }
        bool walkable() const { return walkable_; }
        GridNode * parent() const { return parent_; }

        // mutators
        void setRow(int row) { row_ = row; }
        void setColumn(int column) { column_ = column; }
        void setFScore(int fScore) { fScore_ = fScore; }
        void setGScore(int gScore) { gScore_ = gScore; }
        void setHScore(int hScore) { hScore_ = hScore; }
        void setParent(GridNode * parent) { parent_ = parent; }
        void setWalkable(bool walkable) { walkable_ = walkable; }

        bool operator>(const GridNode &other) const;


        void setScores(int fScore, int gScore, int hScore);

        int compare(GridNode * node);

        Point centerPoint();

        void reset();
        std::string toString();

};


#endif

