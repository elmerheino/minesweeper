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
#include <format>

SDL_Window *win = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* tile_closed = NULL;
SDL_Surface* tile_empty = NULL; // Blank tile
SDL_Surface* tile_mine = NULL;
SDL_Surface* number_tiles[9];
SDL_Surface* tile_flag = NULL;

int grid_width = 30;
int grid_height = 20;

int window_width = (grid_width/2)*50;
int window_height = (grid_height/2)*50;

bool game_over = false;

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize" << std::endl;
        return false;
    }
    win = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_ALLOW_HIGHDPI);
    
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
    tile_flag = SDL_LoadBMP("media/flag.bmp");
    
    for (int i = 1; i <= 8; i++) {
        std::string path = std::format("media/numberTile-{}.bmp",i);
        std::cout << "Loading file: " << path << std::endl;
        number_tiles[i] = SDL_LoadBMP(path.c_str());
        if (number_tiles[i] == NULL) {
            return false;
        }
    }
    
    if (tile_closed == NULL || tile_mine == NULL || tile_empty == NULL || tile_flag == NULL) {
        return false;
    }
    return true;
}

void renderState(Grid* g) {
    SDL_Rect pos = {0,0,50,50};
    for (int i = 0; i < grid_width; i++) {
        for (int j = 0; j < grid_height; j++) {
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
                case 20:
                    // Render a flag.
                    SDL_BlitSurface(tile_flag, NULL, screenSurface, &pos);
                    break;
                default:
                    break;
            }
            int tile_state = g->getTile(i,j) - 2;
            if (tile_state <= 8 && tile_state >= 0) {
                SDL_BlitSurface(number_tiles[tile_state], NULL, screenSurface, &pos);
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
    std::pair<int, int> result(x*grid_width/window_width, y*grid_height/window_height);
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
    
    Grid grid(grid_width,grid_height,2);
    
    // Place mines
    renderState(&grid);
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

                if (winEvent.button.button == SDL_BUTTON_LEFT) {
                    if (!game_over && grid.revealTile(tile_x, tile_y)) {
                        // Game over
                        std::cout << "Game over !!!" << std::endl;
                        game_over = true;
                        grid.revealAllMines();
                        renderState(&grid);
                        SDL_UpdateWindowSurface(win);
                    }
                    renderState(&grid);
                    SDL_UpdateWindowSurface(win);
                    
                    std::cout << "Mouse button down at: " << x << " " << y << std::endl;
                    std::cout << tile_x << " " << tile_y << std::endl;
                    std::cout << "There is a type of tile: " << grid.getTile(tile_x, tile_y) << std::endl;

                } else if (winEvent.button.button == SDL_BUTTON_RIGHT) {
                    // Add a flag
                    grid.insertFlag(tile_x, tile_y);
                    renderState(&grid);
                    SDL_UpdateWindowSurface(win);
                    
                    if (!game_over && grid.isGameWon()) {
                        game_over = true;
                        std::cout << "You won, all the mines have been flagged" << std::endl;
                    }
                }
            }
        }
    }
    
    close();
    return 0;
}
