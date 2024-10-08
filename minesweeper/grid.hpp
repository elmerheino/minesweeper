//
//  grid.hpp
//  minesweeper
//
//  Created by Elmer Heino on 15.9.2024.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>

class Grid {
    int states[10][10];
    
public:
    Grid();
    void revealTile(int row, int column);
    int getTile(int row, int column);
};

#endif /* grid_hpp */
