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
#include <format>

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
            std::cout << std::format(" ({},{}) ", i, j);
        }
    }
    std::cout << std::endl;
}

int Grid::getTile(int row, int column) {
    return state.at(column*width+row);
}

bool Grid::hasMine(int row, int column) {
    bool res = mines.contains(column*width+row);
    return res;
}

void Grid::setTile(int row, int column, int value) {
    state.at(column*width+row) = value;
}

int Grid::minesAround(int row, int column) {
    int mines_around = 0;
    if (hasMine(row+1, column)) {
        mines_around++;
    }
    if (hasMine(row, column+1)) {
        mines_around++;
    }
    if (hasMine(row-1, column)) {
        mines_around++;
    }
    if (hasMine(row, column-1)) {
        mines_around++;
    }
    if (hasMine(row+1, column+1)) {
        mines_around++;
    }
    if (hasMine(row-1, column-1)) {
        mines_around++;
    }
    if (hasMine(row+1, column-1)) {
        mines_around++;
    }
    if (hasMine(row-1, column+1)) {
        mines_around++;
    }
    return mines_around;
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
    if (getTile(row, col) != 0) { // If already visited, return
        return;
    }
    if (minesAround(row, col) != 0) {
        setTile(row, col, 2+minesAround(row, col));
        return;
    }
    if (hasMine(row, col)) { // If there is a mine, return
        return;
    }
    setTile(row, col, 2+minesAround(row, col));
    revealTileRecursive(row-1, col); // Open the one above
    revealTileRecursive(row, col-1); // Open the one to the left
    revealTileRecursive(row+1, col);
    revealTileRecursive(row, col+1);
}

bool Grid::revealTile(int row, int column) { // Returns true of there is a mine
    if (!withinRange(row, column)) {
        return false;
    }
    if (hasMine(row, column)) {
        setTile(row, column, 1);
        return true;
    } else {
        int mines_around_here = minesAround(row, column);
        setTile(row, column, 2+mines_around_here);
        // Start the recursion
        revealTileRecursive(row-1, column); // Open the one above
        revealTileRecursive(row, column-1); // Open the one to the left
        revealTileRecursive(row+1, column); // Open the one below
        revealTileRecursive(row, column+1); // Open the one to the right
    }
    return false;
}
