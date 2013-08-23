#ifndef TEITRUS_GRID_H_
#define TEITRUS_GRID_H_

#include <vector>
#include "grid_block.h"

// Constants
const int kGridColumns   = 10;
const int kGridRows      = 16;
const int kGridOriginX   = 20;
const int kGridOriginY   = 20;
const int kGridDimension = 50;

const int kSpawnX = kGridOriginX + (kGridDimension * 4);
const int kSpawnY = kGridOriginY;

class Grid
{
    private:
        GridBlock * grid[kGridRows][kGridColumns];

    public:

        Grid();

};

#endif
