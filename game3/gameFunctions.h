#ifndef GAMEFUNCTIONS_H_INCLUDED
#define GAMEFUNCTIONS_H_INCLUDED

#include <iostream>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "graphics.h"
#include "menu.h"

using namespace std;
extern bool isMenuShown;
void youWin(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {

    SDL_Color White = { 255, 255, 255 };
    SDL_Color Black = { 0, 0, 0 };
    SDL_Color Yellow = { 255, 255, 0 };

    // Get the font used for displaying text
    TTF_Font* font = TTF_OpenFont("OpenSans.ttf", 10);
    if (font == NULL) {
        cout << "Font loading error" << endl;
        return;
    }

    SDL_Surface* gameover = TTF_RenderText_Solid(font, "You won!", Yellow);
    SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Space to play again", White);
    SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
    SDL_Surface* returnMenu = TTF_RenderText_Solid(font, "Press Enter to return Menu", White);
    SDL_Texture* gameoverText = SDL_CreateTextureFromSurface(renderer, gameover);
    SDL_Texture* retryText= SDL_CreateTextureFromSurface(renderer, retry);
    SDL_Texture* scoreText = SDL_CreateTextureFromSurface(renderer, score);
    SDL_Texture* returnMenuText= SDL_CreateTextureFromSurface(renderer, returnMenu );
    SDL_Rect gameoverRect;
    SDL_Rect retryRect;
    SDL_Rect scoreRect;
    SDL_Rect returnMenuRect;
    gameoverRect.w = 200;
    gameoverRect.h = 100;
    gameoverRect.x = ((scale * wScale) / 2) - (gameoverRect.w / 2);
    gameoverRect.y = ((scale * wScale) / 2) - (gameoverRect.h / 2) - 50;
    retryRect.w = 300;
    retryRect.h = 50;
    retryRect.x = ((scale * wScale) / 2) - (retryRect.w / 2);
    retryRect.y = (((scale * wScale) / 2) - (retryRect.h / 2)) + 150;
    returnMenuRect.w = 300;
    returnMenuRect.h = 50;
    returnMenuRect.x = ((scale * wScale) / 2) - (returnMenuRect.w / 2);
    returnMenuRect.y = (((scale * wScale) / 2) - (returnMenuRect.h / 2)) + 200;
    scoreRect.w = 100;
    scoreRect.h = 30;
    scoreRect.x = ((scale * wScale) / 2) - (scoreRect.w / 2);
    scoreRect.y = 0;
    SDL_RenderCopy(renderer, gameoverText, NULL, &gameoverRect);
    SDL_RenderCopy(renderer, retryText, NULL, &retryRect);
    SDL_RenderCopy(renderer, scoreText, NULL, &scoreRect);
    SDL_RenderCopy(renderer, returnMenuText, NULL, &returnMenuRect);
    TTF_CloseFont(font);

    // Show victory screen while space has not been pressed
    while (true) {
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                return;
            }

        }

    }

}
#endif // GAMEFUNCTIONS_H_INCLUDED
