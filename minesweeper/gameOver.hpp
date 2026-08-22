//
//  gameOver.hpp
//  minesweeper
//
//  Created by Elmer Heino on 13.12.2024.
//

#ifndef gameOver_hpp
#define gameOver_hpp

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

#endif /* gameOver_hpp */
