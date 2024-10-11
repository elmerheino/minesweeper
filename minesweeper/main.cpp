//
//  main.cpp
//  minesweeper
//
//  Created by Elmer Heino on 15.9.2024.
//
#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <set>
#include "grid.hpp"

SDL_Window *win = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* tile_closed = NULL;
SDL_Surface* tile_empty = NULL; // Blank tile
SDL_Surface* tile_mine = NULL;
SDL_Surface* number_tiles[9];

int state[10][10];
bool opened[10][10];
std::set<int> mines;

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize" << std::endl;
        return false;
    }
    win = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 250, 250, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if (win == NULL) {
        return false;
    }
    
    screenSurface = SDL_GetWindowSurface(win);
    if (screenSurface == NULL) {
        return false;
    }
    
    return true;
};

bool loadMedia() {
    tile_closed = SDL_LoadBMP("media/tile.bmp");
    tile_mine = SDL_LoadBMP("media/mine.bmp");
    tile_empty = SDL_LoadBMP("media/empty.bmp");
    
    if (tile_closed == NULL || tile_mine == NULL || tile_empty == NULL) {
        return false;
    }
    
    
    return true;
}

void renderState(Grid* g) {
    SDL_Rect pos = {0,0,50,50};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            pos = {i*50,j*50,50,50};
            switch (g->getTile(i,j)) {
                case 0:
                    SDL_BlitSurface(tile_closed, NULL, screenSurface, &pos);
                    break;
                case 1:
                    SDL_BlitSurface(tile_mine, NULL, screenSurface, &pos);
                    break;
                case 2:
                    SDL_BlitSurface(tile_empty, NULL, screenSurface, &pos);
                    break;
                default:
                    break;
            }
        }
    }
}

void close() {
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

std::pair<int, int> getTileLocationFromScreen(int x, int y){
    std::pair<int, int> result(x*10/250, y*10/250);
    return result;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    init();
    
    if (!loadMedia()) {
        std::cout << "Problem loading media." << std::endl;
        close();
        return 0;
    }
    
    Grid grid(10,10,10);
    
    // Place mines
    renderState(&grid);
    // renderGrid(10, 10);
    SDL_UpdateWindowSurface(win);
    
    SDL_Event winEvent;
    
    while (true) {
        if (SDL_PollEvent(&winEvent)) {
            if (SDL_QUIT == winEvent.type) {
                break;
            }
            if (winEvent.type == SDL_MOUSEBUTTONDOWN) {
                int x = winEvent.button.x;
                int y = winEvent.button.y;
                int tile_x = getTileLocationFromScreen(x,y).first;
                int tile_y = getTileLocationFromScreen(x,y).second;
                                
                grid.revealTile(tile_x, tile_y);
                renderState(&grid);
                SDL_UpdateWindowSurface(win);
                
                std::cout << "Mouse button down at: " << x << " " << y << std::endl;
                std::cout << tile_x << " " << tile_y << std::endl;
                std::cout << "There is a type of tile: " << grid.getTile(tile_x, tile_y) << std::endl;
            }
        }
    }
    
    close();
    return 0;
}
