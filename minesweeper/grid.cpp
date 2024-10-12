//
//  grid.cpp
//  minesweeper
//
//  Created by Elmer Heino on 15.9.2024.
//

#include "grid.hpp"
#include <iostream>
#include <set>
#include <vector>


Grid::Grid(int width_, int height_, int no_of_mines) {
    std::cout << "Initialized grid" << std::endl;
    width = width_;
    height = height_;
    // Place mines
    placeMines(no_of_mines);
    // Prepare the state
    prepareState();
}

void Grid::placeMines(int no_of_mines) {
    std::mt19937 gen(random());
    std::uniform_int_distribution<> distr(0,width*height);
    
    int i = 0;
    while (i < no_of_mines) {
        int mine = distr(gen);
        if (!mines.contains(mine)) {
            mines.insert(mine);
        } else {
            continue;
        }
        i = i + 1;
    }
}

void Grid::prepareState() {
    for (int i = 0; i <= width; i++) {
        for (int j = 0; j <= height; j++) {
            state.push_back(0); // In the beginning all are unopened.
            std::cout << i << " " << j << std::endl;
        }
    }
}

int Grid::getTile(int row, int column) {
    return state.at(row*width+column);
}

bool Grid::hasMine(int row, int column) {
    bool res = mines.contains(row*width+column);
    return res;
}

void Grid::setTile(int row, int column, int value) {
    state.at(row*10+column) = value;
}

int Grid::minesAround(int row, int column) {
    return 0;
}

bool Grid::withinRange(int row, int col) {
    if (row >= 0 && row < width && col >= 0 && col < height ) {
        return true;
    }
    return false;
}

void Grid::revealTileRecursive(int row, int col) {
    if (!withinRange(row, col)) { // If out of range, return
        return;
    }
    if (hasMine(row, col)) { // If there is a mine, return
        return;
    } else { // Else, reveal the tiles around
        setTile(row, col, 2);
        revealTileRecursive(row-1, col); // Open the one above
        revealTileRecursive(row, col-1); // Open the one to the left
        revealTileRecursive(row-1, col-1);
        // Somehow these lines cause segmentation fault
        // revelTileRecursive(row+1, col);
        // revelTileRecursive(row, col+1);
    }
}

bool Grid::revealTile(int row, int column) {
    if (!withinRange(row, column)) {
        return false;
    }
    if (hasMine(row, column)) {
        setTile(row, column, 1);
        return true;
    } else {
        setTile(row, column, 2+minesAround(row, column)); // TODO: make this recursive
        revealTileRecursive(row, column);
    }
    return false;
}
