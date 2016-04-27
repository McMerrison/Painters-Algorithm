#ifndef GRID_H
#define GRID_H

include "pixel.h"

class Grid
{
  public:
    Pixel grid[][];
    
    // Constructor
    Grid(int x, int y);
};

#endif

