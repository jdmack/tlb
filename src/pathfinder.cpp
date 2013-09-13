
#include <list>
#include "pathfinder.h"
#include "grid.h"
#include "grid_node.h"
#include "level.h"

Pathfinder::Pathfinder(Level * level)
{
    level_ = level;
}

std::list<GridNode *> Pathfinder::run(GridNode * start_node, GridNode * end_node)
{
    reset();

    // 1. Add the starting square (or node) to the open list.
    open_list.push_back(start_node);

    GridNode * current_node = nullptr;

    std::list<GridNode *> path;

    // 2. Repeat the following:
    while(true) {
        // a) Look for the lowest F cost square on the open list. We refer to this as the current square.
        if(!open_list.empty()) {

            open_list.sort();

            current_node = open_list.front();
            open_list.pop_front();

        }
        else { 
            // Return empty list for "no path"
            return std::list<GridNode *>();
        }

        // b) Switch it to the closed list.
        closed_list.push_back(current_node);

        // c) For each of the 8 squares adjacent to this current square
        GridNode * adjacent_node = nullptr;
        int g_cost_inc = 0;
        for(int i = 0; i < 8; i++) {
            switch(i) {
                case 0:
                    adjacent_node = level_->grid()->node(current_node->row() - 1, current_node->column() - 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                case 1:
                    adjacent_node = level_->grid()->node(current_node->row() - 1, current_node->column());
                    g_cost_inc = kNodeCostVer;
                    break;
                case 2:
                    adjacent_node = level_->grid()->node(current_node->row() - 1, current_node->column() + 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                case 3:
                    adjacent_node = level_->grid()->node(current_node->row(), current_node->column() - 1);
                    g_cost_inc = kNodeCostHor;
                    break;
                case 4:
                    adjacent_node = level_->grid()->node(current_node->row(), current_node->column() + 1);
                    g_cost_inc = kNodeCostHor;
                    break;
                case 5:
                    adjacent_node = level_->grid()->node(current_node->row() + 1, current_node->column() - 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                case 6:
                    adjacent_node = level_->grid()->node(current_node->row() + 1, current_node->column());
                    g_cost_inc = kNodeCostVer;
                    break;
                case 7:
                    adjacent_node = level_->grid()->node(current_node->row() + 1, current_node->column() + 1);
                    g_cost_inc = kNodeCostDia;
                    break;
            }
        
            // If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.
            if((!adjacent_node->walkable()) || (closed_list_contains(adjacent_node))) {
                continue;
            }

            // If it isn't on the open list, add it to the open list. Make the current square the parent of this
            // square. 
            if(!open_list_contains(adjacent_node)) {
                open_list.push_back(adjacent_node);
                adjacent_node->set_parent(current_node);

                // Record the F, G, and H costs of the square.
                adjacent_node->set_g_score(current_node->g_score() + g_cost_inc);
                adjacent_node->set_h_score((std::abs(adjacent_node->row() - end_node->row()) + std::abs(adjacent_node->column() - 
                    end_node->column())) * kNodeCostHor);
                adjacent_node->set_f_score(adjacent_node->g_score() + adjacent_node->h_score());
            }

            // If it is on the open list already, check to see if this path to that square is better, using G cost
            // as the measure. A lower G cost means that this is a better path. If so, change the parent of
            // the square to the current square, and recalculate the G and F scores of the square. If you are
            // keeping your open list sorted by F score, you may need to resort the list to account for the
            // change.
            else {
                if((current_node->g_score() + g_cost_inc) < adjacent_node->g_score()) {
                    adjacent_node->set_parent(current_node);
                    adjacent_node->set_g_score(current_node->g_score() + g_cost_inc);
                    adjacent_node->set_f_score(adjacent_node->g_score() + adjacent_node->h_score());
                }
            }
        }

        // d) Stop when you:
        // Add the target square to the closed list, in which case the path has been found (see note
        // below), or
        // Fail to find the target square, and the open list is empty. In this case, there is no path.
        if((current_node->row() == end_node->row()) && (current_node->column() == end_node->column())) {
            break;
        }
    }

    // 3.  Save the path. Working backwards from the target square, go from each square to its parent square
    // until you reach the starting square. That is your path.
    GridNode * node = end_node;
    while(end_node->parent() != nullptr) {
        path.push_front(node);
        node = node->parent();
    }

    return path;
}

void Pathfinder::reset()
{
    open_list.clear();
    closed_list.clear();
}

bool Pathfinder::open_list_contains(GridNode * node)
{
    std::list<GridNode *>::iterator it = open_list.begin();
    for(int i = 0; i < open_list.size(); i++) {
        if(((*it)->row() == node->row()) && ((*it)->column() == node->column())) {
            return true;
        }
        ++it;
    }

    return false;
}

bool Pathfinder::closed_list_contains(GridNode * node)
{
    std::list<GridNode *>::iterator it = closed_list.begin();
    for(int i = 0; i < closed_list.size(); i++) {
        if(((*it)->row() == node->row()) && ((*it)->column() == node->column())) {
            return true;
        }
        ++it;
    }

    return false;
}

/*
  _____________________________ 
 |         |         |         |
 | row - 1 | row - 1 | row - 1 |
 | col - 1 | col     | col + 1 |
 |         |         |         |
 |_________|_________|_________|
 |         |         |         |
 | row     | current | row     |
 | col - 1 |         | col + 1 |
 |         |         |         |
 |_________|_________|_________|
 |         |         |         |
 | row + 1 | row + 1 | row + 1 |
 | col - 1 | col     | col + 1 |
 |         |         |         |
 |_________|_________|_________|
*/
