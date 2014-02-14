#ifndef TLB_GRID_NODE_H_
#define TLB_GRID_NODE_H_

const int kGridNodeWidth  = 48;
const int kGridNodeHeight = 48;

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
        int f_score_;
        int g_score_;
        int h_score_;
        bool walkable_;

        GridNode * parent_;

    public:
        // constructors
        GridNode();
        GridNode(int row, int column);

        // accessors
        int row() const { return row_; }
        int column() const { return column_; }
        int f_score() const { return f_score_; }
        int g_score() const { return g_score_; }
        int h_score() const { return h_score_; }
        bool walkable() const { return walkable_; }
        GridNode * parent() const { return parent_; }

        // mutators
        void set_row(int row) { row_ = row; }
        void set_column(int column) { column_ = column; }
        void set_f_score(int f_score) { f_score_ = f_score; }
        void set_g_score(int g_score) { g_score_ = g_score; }
        void set_h_score(int h_score) { h_score_ = h_score; }
        void set_parent(GridNode * parent) { parent_ = parent; }

        void set_scores(int f_score, int g_score, int h_score);

        int compare(GridNode * node);

        Point center_point();

        void reset();
};


#endif

