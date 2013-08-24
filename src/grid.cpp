#include <cstdlib>
#include "grid.h"

Grid::Grid()
{
    for(int i = 0; i < kGridRows; i++) {
        for(int j = 0; j < kGridColumns; j++) {
            //grid[i][j] = NULL;
        }
    }
}
