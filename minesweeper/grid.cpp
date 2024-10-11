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
    std::uniform_int_distribution<> distr(1,width*height);
    
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
    return state.at(row*10+column);
}

bool Grid::hasMine(int row, int column) {
    bool res = mines.contains(row*10+column);
    return res;
}

void Grid::setTile(int row, int column, int value) {
    state.at(row*10+column) = value;
}

int Grid::minesAround(int row, int column) {
    return 0;
}

bool Grid::revealTile(int row, int column) {
    if (hasMine(row, column)) {
        setTile(row, column, 1);
        return false;
    } else {
        setTile(row, column, 2+minesAround(row, column)); // TODO: make this recursive
    }
    return true;
}
