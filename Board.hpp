#ifndef BOARD_H


#define BOARD_H
#include "constant.hpp"
#include "SDL.h"
#include "IO.hpp"
#undef main

class IO;
class Shape;
class Board {
private:
    int _board[BOARD_HEIGHT+1][BOARD_WIDTH+1];
    void freeRow (int full_row,IO& mainIO, Shape curShape);
public:
    Board();
    int *getCurBoard();
    void handleFullRow (IO& mainIO, Shape curShape, const int min_row, int& plus_point);
    void updateBoard (const int *block,const int min_row,const int min_col);
};
#endif
