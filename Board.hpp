#ifndef BOARD_H
#define BOARD_H

#include "constant.hpp"
#include <SDL.h>
#undef main


class Board {
private:
    int _board[BOARD_HEIGHT+1][BOARD_WIDTH+1];
    void freeRow (int full_row);
public:
    Board();
    int *getCurBoard();
    void handleFullRow (int min_row, int& plus_point);
    void updateBoard (int *block,int min_row,int min_col);
};
#endif
