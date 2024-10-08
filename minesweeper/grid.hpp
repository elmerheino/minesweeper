//
//  grid.hpp
//  minesweeper
//
//  Created by Elmer Heino on 15.9.2024.
//

#ifndef grid_hpp
#define grid_hpp

#include <stdio.h>
#include <set>

class Grid {
    int states[10][10]; // 0 unopened, 1 opened, 1+1..9+1 number of mines nearby
    std::set<int> mines;
    
public:
    Grid();
    void revealTile(int row, int column);
    int getTile(int row, int column);
    bool hasMine(int row, int column);
    int minesAround(int row, int column);
};

#endif /* grid_hpp */
