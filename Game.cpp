#include "Game.hpp"
#include "Shape.hpp"
#include "IO.hpp"
#include "Board.hpp"
#include "constant.hpp"
#include <SDL.h>


Game::Game() : _point(0) {};

void shapeHandle (Shape& curShape,IO& mainIO, int* board, bool& is_delay, bool& is_quit, int& plus_point);

void Game::showGreetingMes(IO& mainIO) {
    SDL_Rect greetingRect = {0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT/6};
    mainIO.displayText("Game Start!",NOTIF_FONT_SIZE,greetingRect,PURE_WHITE);
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
        mainIO.updateScreen();
        mBoard.handleFullRow(mainIO,curShape,min_row,plus_point);
        if (plus_point != 0) {
            addPoint( plus_point );
            mainIO.displayPoint(getPoint());
        } else {
            mBoard.updateBoard(shape,min_row,min_col);
            mainIO.updateScreen();
        }
        if (is_quit) {
            break;
        }
    } while (!isOver(shape,min_row));

    bool inEffect = false;
    mainIO.drawCurBoard(board,shape,min_row,min_col, inEffect);
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
        bool inEffect = false;
        mainIO.drawCurBoard(board,shape,min_row,min_col,inEffect);

        if(delay_counter % GAME_DELAY_BEAT == 0) curShape.falling();
        min_row = curShape.getMinRow();
        min_col = curShape.getMinCol();
        delay_counter++;
        is_delay ? (delay_counter++) : (delay_counter = GAME_DELAY_BEAT); // delay.
    }
}


void Game::showEndGameMes (IO& mainIO) {
    mainIO.displayPoint(getPoint());
    SDL_Rect endGameMesRect = {0,0,MAIN_SCREEN_WIDTH,MAIN_SCREEN_HEIGHT/6};
    mainIO.clearRender();
    mainIO.displayText("Game Over!",NOTIF_FONT_SIZE,endGameMesRect,PURE_BLACK);
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
