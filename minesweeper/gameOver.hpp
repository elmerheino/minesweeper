//
//  gameOver.hpp
//  minesweeper
//
//  Created by Elmer Heino on 13.12.2024.
//

#include <stdio.h>
#include <set>
#include <vector>
#include <random>
#include <SDL2/SDL.h>

class gameOver {
private:
    int var;
    SDL_Surface* gameOverGraphic;
public:
    gameOver();
    void render(SDL_Surface* screen);
    bool load_graphics();
};
