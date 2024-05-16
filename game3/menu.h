#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <ctime>
#include <SDL_ttf.h>
#include "renderFunctions.h"
#include "gameFunctions.h"
#include "graphics.h"
#include "gamePlay.h"
using namespace std;

const int WINDOW_WIDTH = 25;
const int WINDOW_HEIGHT = 25;
extern bool isMenuShown;
struct Button {
    SDL_Rect rect;
    SDL_Texture* texture;
    void (*onClick)();
};

void OnClickEasy() {
    cout << "Easy được chọn" << endl;
    if (TTF_Init() < 0) {
        cout << "Error: " << TTF_GetError() << endl;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH*25+1, WINDOW_HEIGHT*25+1, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    runGame(renderer, 25, 25, 1);

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void OnClickHard() {
    cout << "Khó được chọn" << endl;
    if (TTF_Init() < 0) {
        cout << "Error: " << TTF_GetError() << endl;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH*25+1, WINDOW_HEIGHT*25+1, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    runGame(renderer, 25, 25, 2);

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void OnClickPlay() {
    cout << "Play được chọn" << endl;
    isMenuShown = false;
    // Hiển thị nút "Easy" và "Hard" khi nhấn nút "Play"
}

void OnClickQuit() {
    cout << "Quit được chọn" << endl;
    exit(0);
}

bool IsMouseHover(const SDL_Rect& rect, int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

void HandleButtonClick(Button buttons[], int buttonCount, int mouseX, int mouseY) {
    for (int i = 0; i < buttonCount; ++i) {
        if (mouseX >= buttons[i].rect.x && mouseX <= buttons[i].rect.x + buttons[i].rect.w &&
            mouseY >= buttons[i].rect.y && mouseY <= buttons[i].rect.y + buttons[i].rect.h) {
            buttons[i].onClick();
            break;
        }
    }
}

void RenderButton(SDL_Renderer* renderer, Button& button, int mouseX, int mouseY) {
    if (IsMouseHover(button.rect, mouseX, mouseY)) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng
    } else {
        SDL_SetRenderDrawColor(renderer, 0,30,144,255); // Màu mặc định
    }

    SDL_RenderFillRect(renderer, &button.rect);
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}

void RunMenu(SDL_Renderer* renderer) {
    Button easyButton = {{140, 250, 150, 70}, NULL, OnClickEasy};
    Button hardButton = {{340, 250, 150, 70}, NULL, OnClickHard};
    Button exitButton = {{240, 400, 150, 70}, NULL, OnClickQuit};
    Button playButton = {{240, 250, 150, 70}, NULL, OnClickPlay};
    easyButton.texture = IMG_LoadTexture(renderer, "img\\easy.png");
    hardButton.texture = IMG_LoadTexture(renderer, "img\\hard.png");
    exitButton.texture = IMG_LoadTexture(renderer, "img\\quit.png");
    playButton.texture = IMG_LoadTexture(renderer, "img\\play.png");

    Button buttons[] = {playButton, exitButton, easyButton, hardButton};
    const int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

    bool quit = false;
    SDL_Event e;
    int mouseX = 0, mouseY = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mouseX, &mouseY);
                HandleButtonClick(buttons, buttonCount, mouseX, mouseY);
            } else if (e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&mouseX, &mouseY);
            }

        }

        SDL_RenderClear(renderer);
        SDL_Texture* background = IMG_LoadTexture(renderer, "img\\bg2.png");
        SDL_RenderCopy(renderer, background, NULL, NULL);

        if (isMenuShown) {
            RenderButton(renderer, playButton, mouseX, mouseY);
            RenderButton(renderer, exitButton, mouseX, mouseY);

        } else {
            RenderButton(renderer, easyButton, mouseX, mouseY);
            RenderButton(renderer, hardButton, mouseX, mouseY);
        }
        SDL_RenderPresent(renderer);
    }
}

#endif // MENU_H_INCLUDED
