
#include <list>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "pathfinder_hex.h"
#include "grid.h"
#include "grid_node.h"
#include "utils/logger.h"

static int compare_GridNodes (const GridNode* a, const GridNode* b);

PathfinderHex::PathfinderHex(Grid * grid)
{
    grid_ = grid;
}

std::list<GridNode *> * PathfinderHex::run(GridNode * start_node, GridNode * end_node)
{
    //Logger::write(Logger::string_stream << "PathfinderHex start");
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

        bool even_row = false;
        if(current_node->row() % 2 == 0) {
            even_row = true;
        }

        bool can_go_0 = false;
        bool can_go_1 = false;
        bool can_go_2 = false;
        bool can_go_3 = false;
        bool can_go_4 = false;
        bool can_go_5 = false;

        if(current_node->column() + 1 < grid_->columns()) {
            can_go_2 = is_walkable(current_node->row(), current_node->column() + 1);
        }
        if(current_node->column() > 0) {
            can_go_5 = is_walkable(current_node->row(), current_node->column() - 1);
        }

        if(even_row) {
            if((current_node->row() > 0) && (current_node->column() > 0)) {
                can_go_0 = is_walkable(current_node->row() - 1, current_node->column() - 1);
            }
            if(current_node->row() > 0) {
                can_go_1 = is_walkable(current_node->row() - 1, current_node->column());
            }
            if(current_node->row() + 1 < grid_->rows()) {
                can_go_3 = is_walkable(current_node->row() + 1, current_node->column());
            }
            if((current_node->row() + 1 < grid_->rows()) && (current_node->column() > 0)) {
                can_go_4 = is_walkable(current_node->row() + 1, current_node->column() - 1);
            }
        }
        else {
            if(current_node->row() > 0) {
                can_go_0 = is_walkable(current_node->row() - 1, current_node->column());
            }
            if((current_node->row() > 0) && (current_node->column() + 1 < grid_->columns())) {
                can_go_1 = is_walkable(current_node->row() - 1, current_node->column() + 1);
            }
            if((current_node->row() + 1 < grid_->rows()) && (current_node->column() + 1 < grid_->columns())) {
                can_go_3 = is_walkable(current_node->row() + 1, current_node->column() + 1);
            }
            if(current_node->row() + 1 < grid_->rows()) {
                can_go_4 = is_walkable(current_node->row() + 1, current_node->column());
            }
        }

        //Logger::write(Logger::string_stream << "can_go_0: " << can_go_0);
        //Logger::write(Logger::string_stream << "can_go_1: " << can_go_1);
        //Logger::write(Logger::string_stream << "can_go_2: " << can_go_2);
        //Logger::write(Logger::string_stream << "can_go_3: " << can_go_3);
        //Logger::write(Logger::string_stream << "can_go_4: " << can_go_4);
        //Logger::write(Logger::string_stream << "can_go_5: " << can_go_5);
        //Logger::write(Logger::string_stream);

        for(int i = 0; i < 6; i++) {
/*
    Offset coordinates
            _____
           /     \
          /   1   \
    ,----(  row-1  )----.
   /  0   \ col+1 /  2   \
  / row-1  \_____/  row   \
  \ col    /     \  col+1 /
   \      /       \      /
    )----(         )----(
   /  5   \       /  3   \
  /  row   \_____/  row+1 \
  \  col-1 /     \  col   /
   \      /   4   \      /
    `----(  row+1  )----'
          \ col-1 /
           \_____/
*/


            switch(i) {
                case 0:
                    if(!can_go_0) continue;
                    //Logger::write(Logger::string_stream << "0");

                    if(even_row) {
                        adjacent_node = grid_->node(current_node->row() - 1, current_node->column() - 1);
                    }
                    else {
                        adjacent_node = grid_->node(current_node->row() - 1, current_node->column());
                    }
                    g_cost_inc = kNodeCostAdj;
                    break;
                case 1:
                    if(!can_go_1) continue;
                    //Logger::write(Logger::string_stream << "1");

                    if(even_row) {
                        adjacent_node = grid_->node(current_node->row() - 1, current_node->column());
                    }
                    else {
                        adjacent_node = grid_->node(current_node->row() - 1, current_node->column() + 1);
                    }
                    g_cost_inc = kNodeCostAdj;
                    break;
                case 2:
                    if(!can_go_2) continue;
                    //Logger::write(Logger::string_stream << "2");

                    adjacent_node = grid_->node(current_node->row(), current_node->column() + 1);
                    g_cost_inc = kNodeCostAdj;
                    break;
                case 3:
                    if(!can_go_3) continue;
                    //Logger::write(Logger::string_stream << "3");

                    if(even_row) {
                        adjacent_node = grid_->node(current_node->row() + 1, current_node->column());
                    }
                    else {
                        adjacent_node = grid_->node(current_node->row() + 1, current_node->column() + 1);
                    }
                    g_cost_inc = kNodeCostAdj;
                    break;
                case 4:
                    if(!can_go_4) continue;
                    //Logger::write(Logger::string_stream << "4");

                    if(even_row) {
                        adjacent_node = grid_->node(current_node->row() + 1, current_node->column() - 1);
                    }
                    else {
                        adjacent_node = grid_->node(current_node->row() + 1, current_node->column());
                    }
                    g_cost_inc = kNodeCostAdj;
                    break;
                case 5:
                    if(!can_go_5) continue;
                    //Logger::write(Logger::string_stream << "5");

                    adjacent_node = grid_->node(current_node->row(), current_node->column() - 1);
                    g_cost_inc = kNodeCostAdj;
                    break;
            }
            //Logger::write(Logger::string_stream << "\tConsidering Node: " << adjacent_node->to_string());
        
            // If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.
            //if(closed_list_contains(adjacent_node)) {
            if(!adjacent_node->walkable()) {
                //Logger::write(Logger::string_stream << "\t\tNode not walkable");
                continue;
            }
            if(closed_list_contains(adjacent_node)) {
                //Logger::write(Logger::string_stream << "\t\tNode already on closed list");
                continue;
            }

            // If it isn't on the open list, add it to the open list. Make the current square the parent of this
            // square. 
            if(!open_list_contains(adjacent_node)) {
                open_list.push_back(adjacent_node);
                adjacent_node->set_parent(current_node);

                // Record the F, G, and H costs of the square.
                adjacent_node->set_g_score(current_node->g_score() + g_cost_inc);
                adjacent_node->set_h_score(calculate_h(adjacent_node, end_node));
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

void PathfinderHex::reset()
{
    open_list.clear();
    closed_list.clear();
}

bool PathfinderHex::open_list_contains(GridNode * node)
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

bool PathfinderHex::closed_list_contains(GridNode * node)
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

std::string PathfinderHex::open_list_to_string()
{
    std::ostringstream convert;
    convert << "open_list: \n";
    if(!open_list.empty()) {
        for(std::list<GridNode *>::iterator it = open_list.begin(); it != open_list.end(); ++it) {
            convert << "\t" << (*it)->to_string() << " f_score: " << (*it)->f_score() << std::endl;
        }
    }
    else {
        convert << "empty"; }
    return static_cast<std::ostringstream*>( &(convert) )->str();
}

static int compare_GridNodes (const GridNode* a, const GridNode* b)
{
    return a->f_score() < b->f_score();
}

bool PathfinderHex::is_walkable(int row, int col)
{
    return grid_->node(row, col)->walkable();
}

int PathfinderHex::calculate_h(GridNode * start, GridNode * end)
{
    int start_column = start->column();
    int start_row = start->row();
    int end_column = end->column();
    int end_row = end->row();

    // Use Amit's page to determine distance
    int start_x = start_column - (start_row - (start_row % 2)) / 2;
    int start_z = start_row;
    int start_y = - start_x - start_z;

    int end_x = end_column - (end_row - (end_row % 2)) / 2;
    int end_z = end_row;
    int end_y = - end_x - end_z;

    int distance = (std::abs(end_x - start_x) + std::abs(end_y - start_y) + std::abs(end_z - start_z)) / 2;

    return distance;
}

/*


            _____
           /     \
          /       \
    ,----(         )----.
   /      \       /      \
  /        \_____/        \
  \        /     \        /
   \      /       \      /
    )----(         )----(
   /      \       /      \
  /        \_____/        \
  \        /     \        /
   \      /       \      /
    `----(         )----'
          \       /
           \_____/

    Axial Coordinates
            _____
           /     \
          /   1   \
    ,----(  row-1  )----.
   /  0   \ col+1 /  2   \
  / row-1  \_____/  row   \
  \ col-1  /     \  col+1 /
   \      /       \      /
    )----(         )----(
   /  5   \       /  3   \
  /  row   \_____/  row+1 \
  \  col-1 /     \  col+1 /
   \      /   4   \      /
    `----(  row+1  )----'
          \ col   /
           \_____/

*/
