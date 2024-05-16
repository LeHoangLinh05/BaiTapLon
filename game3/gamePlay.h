#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED
#include "gameFunctions.h"
#include "graphics.h"
#include "renderFunctions.h"
#include "collisionChecker.h"
#include "menu.h"
using namespace std;
extern bool isMenuShown ;
void RunMenu(SDL_Renderer* renderer);
SDL_Texture* backgroundTexture = NULL;
pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
    bool valid = false;
    int x = 100;
    int y = 100;
    srand(time(0));
    x = scale * (rand() % wScale);
    y = scale * (rand() % wScale);
    valid = true;

    // Check all tail blocks and player block
    for (int i = 0; i < tailLength; i++) {

        if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
            valid = false;
        }

    }

    if (!valid) {
        pair<int, int> foodLoc;
        foodLoc = make_pair(-100, -100);
        return foodLoc;
    }

    pair<int, int> foodLoc;
    foodLoc = make_pair(x, y);

    return foodLoc;
}

void gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength) {
    Graphics graphics;

    SDL_Texture* backgroundTexture = NULL;
    SDL_Color Red = { 255, 0, 0 };
    SDL_Color White = { 255, 255, 255 };

    TTF_Font* font = TTF_OpenFont("OpenSans.ttf", 10);
    if (font == NULL) {
        cout << "Font loading error" << endl;
        return;
    }
    backgroundTexture = IMG_LoadTexture(renderer, "img\\grass.png");
    SDL_RenderCopy( renderer, backgroundTexture, NULL, NULL);
    SDL_Rect gameoverRect;
    SDL_Rect retryRect;
    SDL_Rect returnMenuRect;
    gameoverRect.w = 450;
    gameoverRect.h = 250;
    gameoverRect.x = ((scale * wScale) / 2) - (gameoverRect.w / 2);
    gameoverRect.y = ((scale * wScale) / 2) - (gameoverRect.h / 2) - 50;
    SDL_Texture* gameOverTexture = IMG_LoadTexture(renderer, "img\\gameover.png");
    SDL_RenderCopy( renderer, gameOverTexture, NULL, &gameoverRect);
    retryRect.w = 450;
    retryRect.h = 250;
    retryRect.x = ((scale * wScale) / 2) - (retryRect.w / 2);
    retryRect.y = (((scale * wScale) / 2) - (retryRect.h / 2)) + 100;
    SDL_Texture* retryTexture = IMG_LoadTexture(renderer, "img\\retry.png");
    SDL_RenderCopy( renderer, retryTexture, NULL, &retryRect);
    returnMenuRect.w = 550;
    returnMenuRect.h = 350;
    returnMenuRect.x = ((scale * wScale) / 2) - (returnMenuRect.w / 2);
    returnMenuRect.y = (((scale * wScale) / 2) - (returnMenuRect.h / 2)) + 150;
    SDL_Texture* returnMenuTexture = IMG_LoadTexture(renderer, "img\\enter.png");
    SDL_RenderCopy( renderer, returnMenuTexture, NULL, &returnMenuRect);
    SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), White);
    SDL_Texture* scoreText = SDL_CreateTextureFromSurface(renderer, score);
    SDL_Rect scoreRect;
    scoreRect.w = 100;
    scoreRect.h = 30;
    scoreRect.x = ((scale * wScale) / 2) - (scoreRect.w / 2);
    scoreRect.y = 0;
    SDL_RenderCopy(renderer, scoreText, NULL, &scoreRect);
    // Show game over screen while space has not been pressed
    while (true) {
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                return;
            }
             if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                isMenuShown = true;
                RunMenu(renderer);
                return;
            }

        }

    }

}

void runGame(SDL_Renderer* renderer, int scale, int wScale, int a) {
    Graphics graphics;
    Mix_Chunk *gCollision = graphics.loadSound("music\\eat.mp3");
    Mix_Chunk *gHit = graphics.loadSound("music\\doorhit.mp3");
    SDL_Rect player;
    player.x = 0;
    player.y = 0;
    player.h = 0;
    player.w = 0;
    int radius = scale / 4;
    int tailLength = 0;
    vector<int> tailX;
    vector<int> tailY;

    int x = 50;
    int y = 50;
    int prevX = 0;
    int prevY = 0;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool inputThisFrame = false;
    bool redo = false;

    SDL_Rect food;
    food.w = scale;
    food.h = scale;
    food.x = 0;
    food.y = 0;

    pair<int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
    food.x = foodLoc.first;
    food.y = foodLoc.second;

    float time = SDL_GetTicks() / 200;
     backgroundTexture = IMG_LoadTexture(renderer, "img\\pixil1.png");
    while (true) {
        float newTime ;
        if (a==1) {
            newTime = SDL_GetTicks() / 120;
        } else if (a==2) newTime = SDL_GetTicks() / 50;
        float delta = newTime - time;
        time = newTime;
        inputThisFrame = false;
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.type == SDL_KEYDOWN && inputThisFrame == false) {
                if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    up = true;
                    left = false;
                    right = false;
                    down = false;
                    inputThisFrame = true;
                }
                else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    up = false;
                    left = true;
                    right = false;
                    down = false;
                    inputThisFrame = true;
                }
                else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    up = false;
                    left = false;
                    right = false;
                    down = true;
                    inputThisFrame = true;
                }
                else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    up = false;
                    left = false;
                    right = true;
                    down = false;
                    inputThisFrame = true;
                }
            }
        }

        prevX = x;
        prevY = y;

        if (up) {
            y -= delta * scale;
        }
        else if (left) {
            x -= delta * scale;
        }
        else if (right) {
            x += delta * scale;
        }
        else if (down) {
            y += delta * scale;
        }

        if (redo == true) {
            redo = false;
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;
            if (food.x == 0 && food.y == 0) {
                redo = true;
            }
        }

        if (checkCollision(food.x, food.y, x, y)) {
                 graphics.play(gCollision);
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;
            if (food.x == -100 && food.y == -100) {
                redo = true;
            }
            tailLength++;
        }

        if (delta * scale == 25) {
            if (tailX.size() != tailLength) {
                tailX.push_back(prevX);
                tailY.push_back(prevY);
            }
            for (int i = 0; i < tailLength; i++) {
                if (i > 0) {
                    tailX[i - 1] = tailX[i];
                    tailY[i - 1] = tailY[i];
                }
            }
            if (tailLength > 0) {
                tailX[tailLength - 1] = prevX;
                tailY[tailLength - 1] = prevY;
            }
        }

        for (int i = 0; i < tailLength; i++) {
            if (x == tailX[i] && y == tailY[i]) {
                      graphics.play(gHit);
                gameOver(renderer, event, scale, wScale, tailLength);
                x = 50;
                y = 50;
                up = false;
                left = false;
                right = false;
                down = false;
                tailX.clear();
                tailY.clear();
                tailLength = 0;
                redo = false;
                foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
                if (food.x == -100 && food.y == -100) {
                    redo = true;
                }
                food.x = foodLoc.first;
                food.y = foodLoc.second;
            }
        }

        if (x < 0 || y < 0 || x > scale * wScale - scale || y > scale * wScale - scale) {
            graphics.play(gHit);
            gameOver(renderer, event, scale, wScale, tailLength);
            x = 50;
            y = 50;
            up = false;
            left = false;
            right = false;
            down = false;
            tailX.clear();
            tailY.clear();
            tailLength = 0;
            redo = false;
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;
            if (food.x == -100 && food.y == -100) {
                redo = true;
            }
        }
          SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        renderFood(renderer, food, scale, radius);
        renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
        renderScore(renderer, tailLength, scale, wScale);
        SDL_RenderDrawLine(renderer, 0, 0, 0, 25 * 25);
        SDL_RenderDrawLine(renderer, 0, 25*25, 25 * 25, 25 * 25);
        SDL_RenderDrawLine(renderer, 25*25, 25 * 25, 25*25, 0);
        SDL_RenderDrawLine(renderer, 25*25, 0, 0, 0);
        SDL_RenderPresent(renderer);

       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }
}


#endif // GAMEPLAY_H_INCLUDED
