#include "matrix.hpp"
#include "Shape.hpp"
#include "Game.hpp"
#include "constant.hpp"
#include <cstdlib>
#include <ctime>

Shape::Shape() {
    initVoidShape();
    createShape();
    initShapePos();
    initShapeRotation();
}

shape_kind getRandomShapeIndx() {
    return (shape_kind)(rand() % (I_SHAPE-SQUARE_SHAPE+1)+1);
}

void Shape::initShapePos() {
    _min_col = BOARD_WIDTH/2-BLOCK_SIZE/2+1;
    _min_row = -(BLOCK_SIZE+1);
}

void Shape::initShapeRotation() {
    int rotation_type = rand() % 5;
    for (int i = 1; i <= rotation_type; i++) {
        rotateShape();
    }
}

void Shape::createShape() {
    shape_kind indx = getRandomShapeIndx();
    setShapeKind(indx);
    switch (indx) {
    case SQUARE_SHAPE:
        _twoDimension[3][2]=_twoDimension[3][3]=_twoDimension[4][2]=_twoDimension[4][3]=FILLED;
        break;
    case L_SHAPE:
        _twoDimension[2][3]=_twoDimension[3][3]=_twoDimension[4][3]=_twoDimension[4][4]=FILLED;
        break;
    case L_MIRROR:
        _twoDimension[2][3]=_twoDimension[3][3]=_twoDimension[4][3]=_twoDimension[4][2]=FILLED;
        break;
    case N_SHAPE:
        _twoDimension[2][3]=_twoDimension[3][3]=_twoDimension[3][4]=_twoDimension[4][4]=FILLED;
        break;
    case N_MIRROR:
        _twoDimension[2][3]=_twoDimension[3][3]=_twoDimension[3][2]=_twoDimension[4][2]=FILLED;
        break;
    case I_SHAPE:
        _twoDimension[2][3]=_twoDimension[3][3]=_twoDimension[4][3]=_twoDimension[5][3]=FILLED;
        break;
    }
}

void Shape::initVoidShape() {
    for (int i = 1; i <= BLOCK_SIZE; ++i)
        for (int j = 1; j <= BLOCK_SIZE; ++j)
            _twoDimension[i][j] = UNFILLED;
}

int Shape::getMinRow() {
    return _min_row;
}
int Shape::getMinCol() {
    return _min_col;
}

void Shape::setShapeKind (shape_kind indx) {
    _kind = indx;
}

shape_kind Shape::getShapeKind () {
    return _kind;
}

int* Shape::getCurShape() {
    return (int*) _twoDimension;
}

bool Shape::isProperMove(int *board, int cur_min_row, int cur_min_col) {
    int *block = (int*)_twoDimension;
    for (int i = 1; i <= BLOCK_SIZE; ++i) {
        for (int j = 1; j <= BLOCK_SIZE; ++j) {
            int board_row = cur_min_row+i-1;
            int board_col = cur_min_col+j-1;
            if (*(block+i*(BLOCK_SIZE+1)+j) == FILLED) {
                if ((board_row>0 &&((*(board+board_row*(BOARD_WIDTH+1)+board_col)==FILLED
                        ||(board_col-1)*(board_col-BOARD_WIDTH)>0 || board_row>BOARD_HEIGHT)))
                        || (board_row<=0 && (board_col-1)*(board_col-BOARD_WIDTH)>0)) return false;
            }
        }
    }
    return true;
}

void Shape::rotateShape() {
    shape_kind kind = getShapeKind();
    if (kind != SQUARE_SHAPE) {
        turnToTransposeMatrix((int*)_twoDimension);
        swapCols((int*)_twoDimension);
    }
}
void Shape::falling() {
    _min_row++;
}
void Shape::moveLeft() {
    _min_col--;
}
void Shape::moveRight() {
    _min_col++;
}

