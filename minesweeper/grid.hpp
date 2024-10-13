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
#include <vector>
#include <random>

class Grid {
private:
    std::random_device random;
    std::set<int> mines; // This set contains the randomized mines
    std::set<int> flags;
    std::vector<int> state;
    int width;
    int height;
    void placeMines(int no_of_mines);
    void prepareState();
    void setTile(int row, int column, int value);
    bool withinRange(int row, int col);
    void revealTileRecursive(int row, int col);
public:
    Grid(int width, int height, int no_of_mines);
    bool revealTile(int row, int column); // true if no mine, false is mine
    int getTile(int row, int column); // 0 unopened, 1 mine, 2 empty, 2+1 one mine around, 3+n n mines around, 20 flag
    bool hasMine(int row, int column);
    int minesAround(int row, int column);
    void revealAllMines(); // Sets all tiles w/ a mine to 1
    void insertFlag(int row, int column);
    bool isGameWon();
};

#endif /* grid_hpp */
