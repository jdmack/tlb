
#include <list>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "pathfinderHex.h"
#include "grid.h"
#include "gridNode.h"
#include "util/logger.h"

static int compare_GridNodes (const GridNode* a, const GridNode* b);

PathfinderHex::PathfinderHex(Grid * grid)
{
    grid_ = grid;
}

std::list<GridNode *> * PathfinderHex::run(GridNode * startNode, GridNode * endNode)
{
    //Logger::write(Logger::ss << "PathfinderHex start");
    reset();
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

        bool evenRow = false;
        if(currentNode->row() % 2 == 0) {
            evenRow = true;
        }

        bool canGo_0 = false;
        bool canGo_1 = false;
        bool canGo_2 = false;
        bool canGo_3 = false;
        bool canGo_4 = false;
        bool canGo_5 = false;

        if(currentNode->column() + 1 < grid_->columns()) {
            canGo_2 = isWalkable(currentNode->row(), currentNode->column() + 1);
        }
        if(currentNode->column() > 0) {
            canGo_5 = isWalkable(currentNode->row(), currentNode->column() - 1);
        }

        if(evenRow) {
            if((currentNode->row() > 0) && (currentNode->column() > 0)) {
                canGo_0 = isWalkable(currentNode->row() - 1, currentNode->column() - 1);
            }
            if(currentNode->row() > 0) {
                canGo_1 = isWalkable(currentNode->row() - 1, currentNode->column());
            }
            if(currentNode->row() + 1 < grid_->rows()) {
                canGo_3 = isWalkable(currentNode->row() + 1, currentNode->column());
            }
            if((currentNode->row() + 1 < grid_->rows()) && (currentNode->column() > 0)) {
                canGo_4 = isWalkable(currentNode->row() + 1, currentNode->column() - 1);
            }
        }
        else {
            if(currentNode->row() > 0) {
                canGo_0 = isWalkable(currentNode->row() - 1, currentNode->column());
            }
            if((currentNode->row() > 0) && (currentNode->column() + 1 < grid_->columns())) {
                canGo_1 = isWalkable(currentNode->row() - 1, currentNode->column() + 1);
            }
            if((currentNode->row() + 1 < grid_->rows()) && (currentNode->column() + 1 < grid_->columns())) {
                canGo_3 = isWalkable(currentNode->row() + 1, currentNode->column() + 1);
            }
            if(currentNode->row() + 1 < grid_->rows()) {
                canGo_4 = isWalkable(currentNode->row() + 1, currentNode->column());
            }
        }

        //Logger::write(Logger::ss << "canGo_0: " << canGo_0);
        //Logger::write(Logger::ss << "canGo_1: " << canGo_1);
        //Logger::write(Logger::ss << "canGo_2: " << canGo_2);
        //Logger::write(Logger::ss << "canGo_3: " << canGo_3);
        //Logger::write(Logger::ss << "canGo_4: " << canGo_4);
        //Logger::write(Logger::ss << "canGo_5: " << canGo_5);
        //Logger::write(Logger::ss);

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
                    if(!canGo_0) continue;
                    //Logger::write(Logger::ss << "0");

                    if(evenRow) {
                        adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column() - 1);
                    }
                    else {
                        adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column());
                    }
                    gCostInc = kNodeCostAdj;
                    break;
                case 1:
                    if(!canGo_1) continue;
                    //Logger::write(Logger::ss << "1");

                    if(evenRow) {
                        adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column());
                    }
                    else {
                        adjacentNode = grid_->node(currentNode->row() - 1, currentNode->column() + 1);
                    }
                    gCostInc = kNodeCostAdj;
                    break;
                case 2:
                    if(!canGo_2) continue;
                    //Logger::write(Logger::ss << "2");

                    adjacentNode = grid_->node(currentNode->row(), currentNode->column() + 1);
                    gCostInc = kNodeCostAdj;
                    break;
                case 3:
                    if(!canGo_3) continue;
                    //Logger::write(Logger::ss << "3");

                    if(evenRow) {
                        adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column());
                    }
                    else {
                        adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column() + 1);
                    }
                    gCostInc = kNodeCostAdj;
                    break;
                case 4:
                    if(!canGo_4) continue;
                    //Logger::write(Logger::ss << "4");

                    if(evenRow) {
                        adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column() - 1);
                    }
                    else {
                        adjacentNode = grid_->node(currentNode->row() + 1, currentNode->column());
                    }
                    gCostInc = kNodeCostAdj;
                    break;
                case 5:
                    if(!canGo_5) continue;
                    //Logger::write(Logger::ss << "5");

                    adjacentNode = grid_->node(currentNode->row(), currentNode->column() - 1);
                    gCostInc = kNodeCostAdj;
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
                adjacentNode->setHScore(calculateH(adjacentNode, endNode));
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

void PathfinderHex::reset()
{
    openList.clear();
    closedList.clear();
}

bool PathfinderHex::openListContains(GridNode * node)
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

bool PathfinderHex::closedListContains(GridNode * node)
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

std::string PathfinderHex::openListToString()
{
    std::ostringstream convert;
    convert << "openList: \n";
    if(!openList.empty()) {
        for(std::list<GridNode *>::iterator it = openList.begin(); it != openList.end(); ++it) {
            convert << "\t" << (*it)->toString() << " fScore: " << (*it)->fScore() << std::endl;
        }
    }
    else {
        convert << "empty"; }
    return staticCast<std::ostringstream*>( &(convert) )->str();
}

static int compare_GridNodes (const GridNode* a, const GridNode* b)
{
    return a->fScore() < b->fScore();
}

bool PathfinderHex::isWalkable(int row, int col)
{
    return grid_->node(row, col)->walkable();
}

int PathfinderHex::calculateH(GridNode * start, GridNode * end)
{
    int startColumn = start->column();
    int startRow = start->row();
    int endColumn = end->column();
    int endRow = end->row();

    // Use Amit's page to determine distance
    int startX = startColumn - (startRow - (startRow % 2)) / 2;
    int startZ = startRow;
    int startY = - startX - startZ;

    int endX = endColumn - (endRow - (endRow % 2)) / 2;
    int endZ = endRow;
    int endY = - endX - endZ;

    int distance = (std::abs(endX - startX) + std::abs(endY - startY) + std::abs(endZ - startZ)) / 2;

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
