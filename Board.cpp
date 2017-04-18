#include "IO.hpp"
#include "Board.hpp"
#include "Shape.hpp"
#include "constant.hpp"


Board::Board() {
    for (int i = 1; i <= BOARD_HEIGHT; ++i){
        for (int j = 1; j <= BOARD_WIDTH; ++j){
            _board[i][j] = 0;
        }
    }
}

int* Board::getCurBoard() {
    return (int*)_board;
}


void Board::handleFullRow (IO& mainIO, Shape curShape, const int min_row, int& plus_point) {
    bool is_full;
    int i = min_row;
    while (i <= BOARD_HEIGHT && i < min_row+BLOCK_SIZE) {
        is_full = true;
        for (int j = 1; j <= BOARD_WIDTH; ++j) {                             //check i_th row.
            if (_board[i][j] == UNFILLED) is_full = false;
        }
        if(is_full){
            plus_point = PLUS_POINT;
            freeRow(i,mainIO,curShape);
        }
        else
            i++;
    }
}

void Board::freeRow (const int row, IO& mainIO, Shape curShape) {
    mainIO.freeRowEffect((int*)_board,curShape,row);
    for (int i = row; i >= 1; --i)   {
        for (int j = 1; j <= BOARD_WIDTH; ++j) {
            if (i > 1) {
                _board[i][j] = _board[i-1][j];
            } else {
                _board[i][j] = UNFILLED;
            }
        }
    }
}

void Board::updateBoard (const int *block, const int min_row, int min_col) {
    for (int i = 1; i <= BLOCK_SIZE; ++i) {
        for (int j = 1; j <= BLOCK_SIZE; ++j) {
            if (*(block+i*(BLOCK_SIZE+1)+j) == FILLED) {
                int board_row = min_row+i-1;
                int board_col = min_col+j-1;
                _board[board_row][board_col] = *(block+i*(BLOCK_SIZE+1)+j);
            }
        }
    }
}
