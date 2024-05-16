#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <ctime>
#include <SDL_ttf.h>
#include "renderFunctions.h"
#include "collisionChecker.h"
#include "gameFunctions.h"
#include "gamePlay.h"
#include "graphics.h"
#include "menu.h"
using namespace std;

//const int WINDOW_WIDTH = 25;
//const int WINDOW_HEIGHT = 25;

extern bool isMenuShown=true ;



int main(int argc, char* args[]) {
    Graphics graphics;
    graphics.init();
    Mix_Music *gMusic = graphics.loadMusic("music\\SpringWillCome.mp3");
    graphics.play(gMusic);

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_HEIGHT*WINDOW_WIDTH+1, WINDOW_HEIGHT*WINDOW_WIDTH+1 , SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    RunMenu(renderer); // Gọi hàm RunMenu để chạy menu
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


