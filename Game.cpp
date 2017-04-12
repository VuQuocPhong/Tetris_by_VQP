#include "Game.hpp"
#include "Shape.hpp"
#include "IO.hpp"
#include "Board.hpp"
#include "constant.hpp"
#include <SDL.h>


Game::Game() : _point(0) {};

void shapeHandle (Shape& curShape,IO& mainIO, int* board, bool& is_delay, bool& is_quit, int& plus_point);

void Game::showGreetingMes(IO& mainIO) {
    mainIO.displayText("Game Start!",20,0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT/6);
    mainIO.updateRenderer();
    SDL_Delay(NOTIF_DELAY_TIME);
}

void Game::mainLoop (IO& mainIO) {
    Board mBoard;
    int *board, *shape;
    int min_row, min_col;
    bool is_delay;
    bool is_quit = false;

    do {
        //main loop.
        Shape curShape;
        int plus_point = 0;
        board = mBoard.getCurBoard();
        shapeHandle(curShape,mainIO,board,is_delay,is_quit,plus_point);
        shape = curShape.getCurShape();
        min_row = curShape.getMinRow();
        min_col = curShape.getMinCol();
        mBoard.updateBoard(shape,min_row,min_col);
        mainIO.updateRenderer();
        mBoard.handleFullRow(min_row,plus_point);
        if (plus_point != 0) addPoint( plus_point );
        mBoard.updateBoard(shape,min_row,min_col);
        mainIO.updateRenderer();
        if (is_quit){
            break;
        }
    } while (!isOver(shape,min_row));
    mainIO.drawCurBoard(board,shape,min_row,min_col);
}


void shapeHandle (Shape& curShape,IO& mainIO, int* board, bool& is_delay, bool& is_quit, int& plus_point) {
        is_delay = true;
        int delay_counter = 0;
        int* shape = curShape.getCurShape();  //get the two-dimen of block arr.
        int min_row = curShape.getMinRow();
        int min_col = curShape.getMinCol();
        while (curShape.isProperMove(board,min_row+1,min_col) && !is_quit) {
            mainIO.clearRender();
            mainIO.handleInput(board,curShape,is_delay,is_quit);
            mainIO.drawCurBoard(board,shape,min_row,min_col);

            if(delay_counter % GAME_DELAY_BEAT == 0) curShape.falling();
            min_row = curShape.getMinRow();
            min_col = curShape.getMinCol();
            delay_counter++;
            is_delay ? (delay_counter++) : (delay_counter = GAME_DELAY_BEAT); // delay.
        }
}


void Game::showEndGameMes (IO& mainIO) {
    mainIO.displayPoint(getPoint());
    SDL_Delay(NOTIF_DELAY_TIME);
    mainIO.clearRender();
    mainIO.displayText("Game Over!",20,0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT/6);
    SDL_Delay(NOTIF_DELAY_TIME);
}

void Game::addPoint (int plus_point) {
    _point = _point + plus_point;
}

int Game::getPoint() {
    return _point;
}

bool Game::isOver (const int *block,const int min_row) {
    for (int i = 1; i <= BLOCK_SIZE; ++i) {
        for (int j = 1; j <= BLOCK_SIZE; ++j) {
            if (*(block+i*(BLOCK_SIZE+1)+j) == FILLED && i+min_row-1 <= 0) return true;
        }
    }
    return false;
}
