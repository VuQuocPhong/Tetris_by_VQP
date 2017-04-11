#include <iostream>
#include <SDL.h>
#include "IO.hpp"
#include "Shape.hpp"
#include "SDL_ttf.h"
#include "constant.hpp"
#include <string>
#undef main



void IO::handleInput (int* board, Shape &mShape, bool& delay, bool &quit_game) {
    int min_row = mShape.getMinRow();
    int min_col = mShape.getMinCol();
    SDL_Event e;
    if (SDL_PollEvent(&e) && e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
            quit_game = true;
            break;
        case SDLK_DOWN:
            delay = false;
            break;
        case SDLK_LEFT:
            if(mShape.isProperMove(board,min_row,min_col-1)) mShape.moveLeft();
            break;
        case SDLK_RIGHT:
            if(mShape.isProperMove(board,min_row,min_col+1)) mShape.moveRight();
            break;
        case SDLK_UP:
            Shape tmpShape_rotation = mShape;
            tmpShape_rotation.rotateShape();
            if(tmpShape_rotation.isProperMove(board,min_row,min_col)) mShape.rotateShape();
            break;
        }
    }
}

IO::IO () {
    bool success_init = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        success_init = false;
    } else {
        _gWindow = SDL_CreateWindow(
                       "Tetris",
                       SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED,
                       MAIN_SCREEN_WIDTH,
                       MAIN_SCREEN_HEIGHT,
                       SDL_WINDOW_SHOWN);
        if (_gWindow == nullptr) {
            success_init = false;
        } else {
            _gRenderer = SDL_CreateRenderer(_gWindow,-1,SDL_RENDERER_ACCELERATED);
            if (_gRenderer == nullptr) {
                success_init = false;
            } else {
                SDL_SetRenderDrawColor(_gRenderer,0xFF,0xFF,0xFF,0xFF);
            }
        }
    }
    if(!success_init) std::cout << SDL_GetError();
}

void createTexture(SDL_Renderer* gRenderer, SDL_Surface* gSurface, int x, int y, int w, int h) {
    bool success_init = true;
    SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer,gSurface);
    if(gTexture == nullptr) success_init = false;
    else {
        SDL_Rect rect = {x,y,w,h};
        SDL_RenderCopy(gRenderer,gTexture,nullptr,&rect);
        SDL_FreeSurface(gSurface);
        SDL_DestroyTexture(gTexture);
        SDL_RenderPresent(gRenderer);
    }
    if(!success_init) std::cout << SDL_GetError();
}


void DrawRectangle (SDL_Renderer* _gRenderer, int x, int y, int w, int h, int color) {
    SDL_Rect fillrect = {x,y,w,h};
    SDL_SetRenderDrawColor(_gRenderer,color,color,color,color);
    SDL_RenderFillRect(_gRenderer, &fillrect);
}

void IO::drawCurBoard (int* board, int *block, int min_row, int min_col) {
    for (int i = 1; i <= BOARD_HEIGHT; ++i) {
        for (int j = 1; j <= BOARD_WIDTH; ++j) {
            int block_row = i-min_row+1;
            int block_col = j-min_col+1;
            int x = (j-1)*RECTANGLE_SIZE;
            int y = (i-1)*RECTANGLE_SIZE;
            if (block_row >= 1 && block_row <= 5 && block_col <= 5 && block_col >= 1
                    && *(block+block_row*(BLOCK_SIZE+1)+block_col) == FILLED) {
                    DrawRectangle(_gRenderer,x,y,RECTANGLE_SIZE,RECTANGLE_SIZE,0);
            } else {
                if (*(board+i*(BOARD_WIDTH+1)+j) == FILLED)
                    DrawRectangle(_gRenderer,x,y,RECTANGLE_SIZE,RECTANGLE_SIZE,0);
            }
        }
    }
    SDL_RenderPresent(_gRenderer);
    DrawRectangle(_gRenderer,0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT,255);       //main screen background
}

void IO::displayText (const std::string& Text, const int font_size, int x, int y, int w, int h) {
    bool success_init;
    Uint8 rbg = rand() % 255+1;
    SDL_Color TextColor = {rbg,rbg,rbg};
    if(TTF_Init() == -1) {
        success_init = false;
    } else {
        TTF_Font* font = TTF_OpenFont(FONT_PATH.c_str(),font_size);
        if(font == nullptr) success_init = false;
        else {
            SDL_Surface* msg_surface = TTF_RenderText_Solid(font,Text.c_str(),TextColor);
            if(msg_surface == nullptr) success_init = false;
            else {
                createTexture(_gRenderer,
                              msg_surface,
                              x,y,w,h);
            }
        }
    }
    if (!success_init) std::cout << SDL_GetError();
}

void IO::displayPoint(int point) {
    std::string point_str = std::to_string(point);      //convert to point to str for rendering.
    displayText("Point: " + point_str,20,0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT/6);
}

void IO::clearRender() {
    SDL_RenderClear(_gRenderer);
}

void IO::updateRenderer() {
    SDL_RenderPresent(_gRenderer);
}

IO::~IO() {
    SDL_DestroyWindow(_gWindow);
    _gWindow = nullptr;
    SDL_DestroyRenderer(_gRenderer);
    _gRenderer = nullptr;
}



