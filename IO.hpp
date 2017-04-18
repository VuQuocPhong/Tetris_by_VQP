#ifndef IO_HPP
#define IO_HPP
#include "Shape.hpp"
#include "Board.hpp"
#include <SDL.h>
#include <iostream>
class Shape;

class IO {
    SDL_Window* _gWindow;
    SDL_Renderer* _gRenderer;
public:
    IO();
    void drawCurBoard (const int* board, const int* block, const int min_row, const int min_col, bool inEffect = false);
    void handleInput (const int* board, Shape &mShape, bool &delay, bool &quit_game);
    void displayText(const std::string& Text, const int font_size, const SDL_Rect msRect, const uint8_t color);
    void displayPoint (const int point);
    void freeRowEffect (int* board, Shape curShape, const int row);

    void updateScreen();
    void clearRender();
    ~IO();
};
void DrawRectangle (SDL_Renderer* _gRenderer, const SDL_Rect fillRect, const int color);

#endif
