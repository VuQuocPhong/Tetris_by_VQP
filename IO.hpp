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
    void drawCurBoard (int* board, int* block, int min_row, int min_col);
    void handleInput (int* board, Shape &mShape, bool &delay, bool &quit_game);
    void displayText(const std::string& Text, int font_size, int x, int y, int w, int h);
    void displayPoint (int point);
    void updateRenderer();
    void clearRender();
    ~IO();
};

#endif
