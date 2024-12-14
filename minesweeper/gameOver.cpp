//
//  gameOver.cpp
//  minesweeper
//
//  Created by Elmer Heino on 13.12.2024.
//

#include "gameOver.hpp"
#include <iostream>
#include <SDL2/SDL.h>

gameOver::gameOver() {
    load_graphics();
}

void gameOver::render(SDL_Surface* screen) {
    SDL_Rect pos = {750-(1350/2),750-(450/2),450,1350};
    SDL_BlitSurface(gameOverGraphic, NULL, screen, &pos);
}

bool gameOver::load_graphics() {
    gameOverGraphic = SDL_LoadBMP("media/gameover.bmp");
    std::cout << "Loading game over graphic." << std::endl;
    
    if (gameOverGraphic == NULL) {
        return false;
    }
    return true;
}
