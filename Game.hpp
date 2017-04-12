#ifndef GAME_H
#define GAME_H

#include "Board.hpp"
#include "Shape.hpp"
#include "IO.hpp"


class Game {
private:
    int _point;
public:
    Game();

    void showGreetingMes (IO& mainIO);
    void mainLoop (IO& mainIO);
    void showEndGameMes (IO& mainIO);

    void addPoint (int plus_point);
    int getPoint();
    bool isOver (const int *block, const int min_row);
};

#endif
