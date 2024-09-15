//
//  main.cpp
//  minesweeper
//
//  Created by Elmer Heino on 15.9.2024.
//
#include <iostream>
#include <SDL2/SDL.h>

SDL_Window *win = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* tile = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize" << std::endl;
        return false;
    }
    win = SDL_CreateWindow("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 250, 250, SDL_WINDOW_ALLOW_HIGHDPI);
    
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
    tile = SDL_LoadBMP("media/tile.bmp");
    if (tile == NULL) {
        return false;
    }
    return true;
}

void renderGrid(int width, int height) {
    SDL_Rect pos = {0,0,50,50};
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pos = {i*50,j*50,50,50};
            SDL_BlitSurface(tile, NULL, screenSurface, &pos);
        }
    }
}

void close() {
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    init();
    
    if (!loadMedia()) {
        std::cout << "Problem loading media." << std::endl;
        close();
        return 0;
    }
    
    renderGrid(10, 10);
    SDL_UpdateWindowSurface(win);
    
    SDL_Event winEvent;
    
    while (true) {
        if (SDL_PollEvent(&winEvent)) {
            if (SDL_QUIT == winEvent.type) {
                break;
            }
        }
    }
    
    close();
    return 0;
}
