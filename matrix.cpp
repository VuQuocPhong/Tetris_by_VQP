#define SHAPE_SIZE 5
#include <iostream>

// Linear Algebra's Rotating square_matrix algorithm.

void turnToTransposeMatrix (int *square_matrix) {
    for (int i = 1; i <= SHAPE_SIZE; ++i) {
        for (int j = 1; j < i; ++j) {
            int tmp = *(square_matrix+i*(SHAPE_SIZE+1)+j);
            *(square_matrix+i*(SHAPE_SIZE+1)+j) = *(square_matrix+j*(SHAPE_SIZE+1)+i);
            *(square_matrix+j*(SHAPE_SIZE+1)+i) = tmp;
        }
    }
}

void swapCols (int *square_matrix) {
    for (int j = 1; j <= SHAPE_SIZE/2; ++j) {
        for (int i = 1; i <= SHAPE_SIZE; ++i) {
            int tmp = *(square_matrix+i*(SHAPE_SIZE+1)+j);
            *(square_matrix+i*(SHAPE_SIZE+1)+j) = *(square_matrix+i*(SHAPE_SIZE+1)+SHAPE_SIZE-j+1);
            *(square_matrix+i*(SHAPE_SIZE+1)+SHAPE_SIZE-j+1) = tmp;
        }
    }
}
