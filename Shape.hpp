#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "IO.hpp"
#include "Board.hpp"
#include "constant.hpp"

enum shape_kind {
    SQUARE_SHAPE=1,
    L_SHAPE,
    L_MIRROR,
    N_SHAPE,
    N_MIRROR,
    I_SHAPE
};

class Shape {
private:
    shape_kind _kind;
    int _twoDimension[BLOCK_SIZE+1][BLOCK_SIZE+1];
    int _min_row;
    int _min_col;
public:
    Shape();
    void initVoidShape();
    void createShape();
    void initShapePos();
    shape_kind getShapeKind();
    void initShapeRotation();
    void setShapeKind(shape_kind kind);

    int *getCurShape();
    int getMinRow();
    int getMinCol();

    void rotateShape();
    bool isProperMove(const int *board, const int cur_min_row, const int cur_min_col);
    void falling();
    void moveLeft();
    void moveRight();

};

#endif
