
#include <list>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "pathfinder.h"
#include "grid.h"
#include "grid_node.h"
#include "utils/logger.h"

static int compare_GridNodes (const GridNode* a, const GridNode* b);

Pathfinder::Pathfinder(Grid * grid)
{
    grid_ = grid;
}

std::list<GridNode *> * Pathfinder::run(GridNode * start_node, GridNode * end_node)
{
    bool allow_diagonals = true;
    Logger::write(Logger::string_stream << "Pathfinder start");
    reset();
    // 1. Add the starting square (or node) to the open list.
    open_list.push_back(start_node);

    GridNode * current_node = nullptr;

    std::list<GridNode *> * path = new std::list<GridNode *>();

    // 2. Repeat the following:
    while(true) {
        // a) Look for the lowest F cost square on the open list. We refer to this as the current square.
        if(!open_list.empty()) {

            open_list.sort(compare_GridNodes);
            //Logger::write(Logger::string_stream << open_list_to_string());

            current_node = open_list.front();
            open_list.pop_front();

            //Logger::write(Logger::string_stream << "current_node: " << current_node->to_string());
        }
        else { 
            // Return empty list for "no path"
            //return new std::list<GridNode *>();
            break;
        }

        // b) Switch it to the closed list.
        closed_list.push_back(current_node);

        // c) For each of the 8 squares adjacent to this current square
        GridNode * adjacent_node = nullptr;
        int g_cost_inc = 0;
        for(int i = 0; i < 8; i++) {
            bool can_go_left  = false;
            bool can_go_right = false;
            bool can_go_up    = false;
            bool can_go_down  = false;

            if(current_node->column() > 0) {
                can_go_left = is_walkable(current_node->row(), current_node->column() - 1);
            }
            if(current_node->column() + 1 < grid_->columns()) {
                can_go_right = is_walkable(current_node->row(), current_node->column() + 1);;
            }
            if(current_node->row() > 0) {
                can_go_up = is_walkable(current_node->row() - 1, current_node->column());;
            }
            if(current_node->row() + 1 < grid_->rows()) {
                can_go_down = is_walkable(current_node->row() + 1, current_node->column());;
            }

            switch(i) {
                // up/left
                case 0:
                    if(!allow_diagonals) continue;
                    if((current_node->row() - 1 < 0) || (current_node->column() - 1 < 0)) {
                        // invalid node
                        continue;
                    }
                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!can_go_left) ||(!can_go_up)) {
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() - 1, current_node->column() - 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                // up
                case 1:
                    if(current_node->row() - 1 < 0) {
                        // invalid node
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() - 1, current_node->column());
                    g_cost_inc = kNodeCostVer;
                    break;
                // up/right
                case 2:
                    if(!allow_diagonals) continue;
                    if((current_node->row() - 1 < 0) || (current_node->column() + 1 >= grid_->columns())) {
                        // invalid node
                        continue;
                    }
                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!can_go_up) || (!can_go_right)) {
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() - 1, current_node->column() + 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                // left
                case 3:
                    if(current_node->column() - 1 < 0) {
                        // invalid node
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row(), current_node->column() - 1);
                    g_cost_inc = kNodeCostHor;
                    break;
                // right
                case 4:
                    if(current_node->column() + 1 >= grid_->columns()) {
                        // invalid node
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row(), current_node->column() + 1);
                    g_cost_inc = kNodeCostHor;
                    break;
                // down/left
                case 5:
                    if(!allow_diagonals) continue;
                    if((current_node->row() + 1 >= grid_->rows()) || (current_node->column() - 1 < 0)) {
                        // invalid node
                        continue;
                    }
                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!can_go_down) || (!can_go_left)) {
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() + 1, current_node->column() - 1);
                    g_cost_inc = kNodeCostDia;
                    break;
                // down
                case 6:
                    if(current_node->row() + 1 >= grid_->rows()) {
                        // invalid node
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() + 1, current_node->column());
                    g_cost_inc = kNodeCostVer;
                    break;
                // down/right
                case 7:
                    if(!allow_diagonals) continue;
                    if((current_node->row() + 1 >= grid_->rows()) || (current_node->column() + 1 >= grid_->columns())) {
                        // invalid node
                        continue;
                    }
                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!can_go_down) || (!can_go_right)) {
                        continue;
                    }
                    adjacent_node = grid_->node(current_node->row() + 1, current_node->column() + 1);
                    g_cost_inc = kNodeCostDia;
                    break;
            }
            //Logger::write(Logger::string_stream << "\tConsidering Node: " << adjacent_node->to_string());
        
            // If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.
            //if(closed_list_contains(adjacent_node)) {
            if(!adjacent_node->walkable()) {
                Logger::write(Logger::string_stream << "\t\tNode not walkable");
                continue;
            }
            if(closed_list_contains(adjacent_node)) {
                Logger::write(Logger::string_stream << "\t\tNode already on closed list");
                continue;
            }

            // If it isn't on the open list, add it to the open list. Make the current square the parent of this
            // square. 
            if(!open_list_contains(adjacent_node)) {
                open_list.push_back(adjacent_node);
                adjacent_node->set_parent(current_node);

                // Record the F, G, and H costs of the square.
                adjacent_node->set_g_score(current_node->g_score() + g_cost_inc);
                adjacent_node->set_h_score((abs(adjacent_node->row() - end_node->row()) + abs(adjacent_node->column() - 
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
    while(node->parent() != nullptr) {
        path->push_front(node);
        node = node->parent();
    }
    path->push_front(start_node);

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
    for(unsigned int i = 0; i < open_list.size(); i++) {
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
    for(unsigned int i = 0; i < closed_list.size(); i++) {
        if(((*it)->row() == node->row()) && ((*it)->column() == node->column())) {
            return true;
        }
        ++it;
    }

    return false;
}

std::string Pathfinder::open_list_to_string()
{
    std::ostringstream convert;
    convert << "open_list: \n";
    if(!open_list.empty()) {
        for(std::list<GridNode *>::iterator it = open_list.begin(); it != open_list.end(); ++it) {
            convert << "\t" << (*it)->to_string() << " f_score: " << (*it)->f_score() << std::endl;
        }
    }
    else {
        convert << "empty";
    }
    return static_cast<std::ostringstream*>( &(convert) )->str();
}

static int compare_GridNodes (const GridNode* a, const GridNode* b)
{
    return a->f_score() < b->f_score();
}

bool Pathfinder::is_walkable(int row, int col)
{
    return grid_->node(row, col)->walkable();
}

/*
  ____________
 |   |   |   |
 | 0 | 1 | 2 |
 |___|___|___|
 |   |   |   |
 | 3 |   | 4 |
 |___|___|___|
 |   |   |   |
 | 5 | 6 | 7 |
 |___|___|___|
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
