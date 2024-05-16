#ifndef RENDERFUNCTIONS_H_INCLUDED
#define RENDERFUNCTIONS_H_INCLUDED

#include <iostream>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm>
using namespace std;
void filledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int x = centerX - radius; x <= centerX + radius; ++x) {
        for (int y = centerY - radius; y <= centerY + radius; ++y) {
            int distanceSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distanceSquared <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void drawRoundedSquare(SDL_Renderer* renderer, int x, int y, int size, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x + radius, y, size - 2 * radius, size};
    SDL_RenderFillRect(renderer, &rect);
    rect = {x, y + radius, size, size - 2 * radius};
    SDL_RenderFillRect(renderer, &rect);
    filledCircle(renderer, x + radius, y + radius, radius, color);
    filledCircle(renderer, x + size - radius - 1, y + radius, radius, color);
    filledCircle(renderer, x + radius, y + size - radius - 1, radius, color);
    filledCircle(renderer, x + size - radius - 1, y + size - radius - 1, radius, color);
}
void drawRoundedSquareOutline(SDL_Renderer* renderer, int x, int y, int size, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    filledCircle(renderer, x + radius, y + radius, radius, color);
    filledCircle(renderer, x + size - radius - 1, y + radius, radius, color);
    filledCircle(renderer, x + radius, y + size - radius - 1, radius, color);
    filledCircle(renderer, x + size - radius - 1, y + size - radius - 1, radius, color);

    SDL_RenderDrawLine(renderer, x + radius, y, x + size - radius - 1, y); // Top
    SDL_RenderDrawLine(renderer, x + radius, y + size - 1, x + size - radius - 1, y + size - 1); // Bottom
    SDL_RenderDrawLine(renderer, x, y + radius, x, y + size - radius - 1); // Left
    SDL_RenderDrawLine(renderer, x + size - 1, y + radius, x + size - 1, y + size - radius - 1); // Right
}
void renderPlayer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, const vector<int>& tailX, const vector<int>& tailY, int tailLength) {
    // Define color and radius for the player
    SDL_Color playerColor = {30,144,255};
    int playerRadius = scale / 4;

    drawRoundedSquare(renderer, x, y, scale, playerRadius, playerColor);
    for (int i = 0; i < tailLength; ++i) {
        drawRoundedSquare(renderer, tailX[i], tailY[i], scale, playerRadius, playerColor);
    }
}
void renderFood(SDL_Renderer* renderer, SDL_Rect food, int scale, int radius) {
    SDL_Color foodColor = {240,128,128};
    drawRoundedSquare(renderer, food.x, food.y, scale, radius, foodColor);
}

void renderScore(SDL_Renderer* renderer, int tailLength, int scale, int wScale) {
    SDL_Color White = { 255, 255, 255 };
    TTF_Font* font = TTF_OpenFont("OpenSans.ttf", 10);
    if (font == NULL) {
        cout << "Font loading error" << endl;
        return;
    }

    SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), White);
    SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
    SDL_Rect scoreRect;
    scoreRect.w = 100;
    scoreRect.h = 30;
    scoreRect.x = ((scale * wScale) / 2) - (scoreRect.w / 2);
    scoreRect.y = 0;
    SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

    TTF_CloseFont(font);
}

#endif // RENDERFUNCTIONS_H_INCLUDED
