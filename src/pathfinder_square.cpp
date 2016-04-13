#include <list>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "pathfinderSquare.h"
#include "grid.h"
#include "gridNode.h"
#include "util/logger.h"

static int compare_GridNodes (const GridNode* a, const GridNode* b);

PathfinderSquare::PathfinderSquare(Grid * grid)
{
    grid_ = grid;
}

std::list<GridNode *> * PathfinderSquare::run(GridNode * startNode, GridNode * endNode)
{
    bool allowDiagonals = true;
    //Logger::write(Logger::ss << "PathfinderSquare start");
    reset();

    //Logger::write(Logger::ss << "Start: " << startNode->toString());
    //Logger::write(Logger::ss << "End: " << endNode->toString());


    // 1. Add the starting square (or node) to the open list.
    openList.pushBack(startNode);

    GridNode * currentNode = nullptr;

    std::list<GridNode *> * path = new std::list<GridNode *>();

    // 2. Repeat the following:
    while(true) {
        // a) Look for the lowest F cost square on the open list. We refer to this as the current square.
        if(!openList.empty()) {

            openList.sort(compare_GridNodes);
            //Logger::write(Logger::ss << openListToString());

            currentNode = openList.front();
            openList.popFront();

            //Logger::write(Logger::ss << "currentNode: " << currentNode->toString());
        }
        else { 
            // Return empty list for "no path"
            //return new std::list<GridNode *>();
            break;
        }

        // b) Switch it to the closed list.
        closedList.pushBack(currentNode);

        // c) For each of the 8 squares adjacent to this current square
        GridNode * adjacentNode = nullptr;
        int gCostInc = 0;
        for(int i = 0; i < 8; i++) {
            bool canGoLeft  = false;
            bool canGoRight = false;
            bool canGoUp    = false;
            bool canGoDown  = false;

            if(currentNode->column() > 0) {
                canGoLeft = isWalkable(currentNode->row(), currentNode->column() - 1);
            }
            if(currentNode->column() + 1 < grid_->columns()) {
                canGoRight = isWalkable(currentNode->row(), currentNode->column() + 1);;
            }
            if(currentNode->row() > 0) {
                canGoUp = isWalkable(currentNode->row() - 1, currentNode->column());;
            }
            if(currentNode->row() + 1 < grid_->rows()) {
                canGoDown = isWalkable(currentNode->row() + 1, currentNode->column());;
            }

            switch(i) {
                // up/left
                case 0:
                    if(!allowDiagonals) continue;

                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!canGoLeft) || (!canGoUp)) {
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column() - 1);
                    gCostInc = kNodeCostDia;
                    break;
                // up
                case 1:
                    // Check falling off top
                    if(currentNode->row() - 1 < 0) {
                        // invalid node
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column());
                    gCostInc = kNodeCostVer;
                    break;
                // up/right
                case 2:
                    if(!allowDiagonals) continue;

                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!canGoUp) || (!canGoRight)) {
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column() + 1);
                    gCostInc = kNodeCostDia;
                    break;
                // left
                case 3:
                    // Check falling off left
                    if(currentNode->column() - 1 < 0) {
                        // invalid node
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row(), currentNode->column() - 1);
                    gCostInc = kNodeCostHor;
                    break;
                // right
                case 4:
                    // Check falling off right
                    if(currentNode->column() + 1 >= grid_->columns()) {
                        // invalid node
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row(), currentNode->column() + 1);
                    gCostInc = kNodeCostHor;
                    break;
                // down/left
                case 5:
                    if(!allowDiagonals) continue;

                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!canGoDown) || (!canGoLeft)) {
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column() - 1);
                    gCostInc = kNodeCostDia;
                    break;
                // down
                case 6:
                    // Check falling off bottom
                    if(currentNode->row() + 1 >= grid_->rows()) {
                        // invalid node
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column());
                    gCostInc = kNodeCostVer;
                    break;
                // down/right
                case 7:
                    if(!allowDiagonals) continue;

                    // Go diagonal only if the two corner nodes are walkable (don't cut corners)
                    if((!canGoDown) || (!canGoRight)) {
                        continue;
                    }
                    adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column() + 1);
                    gCostInc = kNodeCostDia;
                    break;
            }
            //Logger::write(Logger::ss << "\tConsidering Node: " << adjacentNode->toString());
        
            // If it is not walkable or if it is on the closed list, ignore it. Otherwise do the following.
            //if(closedListContains(adjacentNode)) {
            if(!adjacentNode->walkable()) {
                //Logger::write(Logger::ss << "\t\tNode not walkable");
                continue;
            }
            if(closedListContains(adjacentNode)) {
                //Logger::write(Logger::ss << "\t\tNode already on closed list");
                continue;
            }

            // If it isn't on the open list, add it to the open list. Make the current square the parent of this
            // square. 
            if(!openListContains(adjacentNode)) {
                openList.pushBack(adjacentNode);
                adjacentNode->setParent(currentNode);

                // Record the F, G, and H costs of the square.
                adjacentNode->setGScore(currentNode->gScore() + gCostInc);
                adjacentNode->setHScore((abs(adjacentNode->row() - endNode->row()) + abs(adjacentNode->column() - 
                    endNode->column())) * kNodeCostHor);
                adjacentNode->setFScore(adjacentNode->gScore() + adjacentNode->hScore());
            }

            // If it is on the open list already, check to see if this path to that square is better, using G cost
            // as the measure. A lower G cost means that this is a better path. If so, change the parent of
            // the square to the current square, and recalculate the G and F scores of the square. If you are
            // keeping your open list sorted by F score, you may need to resort the list to account for the
            // change.
            else {
                if((currentNode->gScore() + gCostInc) < adjacentNode->gScore()) {
                    adjacentNode->setParent(currentNode);
                    adjacentNode->setGScore(currentNode->gScore() + gCostInc);
                    adjacentNode->setFScore(adjacentNode->gScore() + adjacentNode->hScore());
                }
            }
        }

        // d) Stop when you:
        // Add the target square to the closed list, in which case the path has been found (see note
        // below), or
        // Fail to find the target square, and the open list is empty. In this case, there is no path.
        if((currentNode->row() == endNode->row()) && (currentNode->column() == endNode->column())) {
            break;
        }
    }

    // 3.  Save the path. Working backwards from the target square, go from each square to its parent square
    // until you reach the starting square. That is your path.
    GridNode * node = endNode;
    while(node->parent() != nullptr) {
        path->pushFront(node);
        node = node->parent();
    }
    path->pushFront(startNode);

    return path;
}

void PathfinderSquare::reset()
{
    openList.clear();
    closedList.clear();
}

bool PathfinderSquare::openListContains(GridNode * node)
{
    std::list<GridNode *>::iterator it = openList.begin();
    for(unsigned int i = 0; i < openList.size(); i++) {
        if(((*it)->row() == node->row()) && ((*it)->column() == node->column())) {
            return true;
        }
        ++it;
    }

    return false;
}

bool PathfinderSquare::closedListContains(GridNode * node)
{
    std::list<GridNode *>::iterator it = closedList.begin();
    for(unsigned int i = 0; i < closedList.size(); i++) {
        if(((*it)->row() == node->row()) && ((*it)->column() == node->column())) {
            return true;
        }
        ++it;
    }

    return false;
}

std::string PathfinderSquare::openListToString()
{
    std::ostringstream convert;
    convert << "openList: \n";
    if(!openList.empty()) {
        for(std::list<GridNode *>::iterator it = openList.begin(); it != openList.end(); ++it) {
            convert << "\t" << (*it)->toString() << " fScore: " << (*it)->fScore() << std::endl;
        }
    }
    else {
        convert << "empty";
    }
    return staticCast<std::ostringstream*>( &(convert) )->str();
}

static int compare_GridNodes (const GridNode* a, const GridNode* b)
{
    return a->fScore() < b->fScore();
}

bool PathfinderSquare::isWalkable(int row, int col)
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
