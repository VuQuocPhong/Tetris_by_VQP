#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#undef main
#include "Board.hpp"
#include "Shape.hpp"
#include "Game.hpp"
#include "IO.hpp"


int main (int argc, char *argv[]) {
    srand(time(nullptr));
    Game newGame;
    IO mainIO;

    newGame.showGreetingMes(mainIO);
    newGame.mainLoop(mainIO);
    newGame.showEndGameMes(mainIO);

    return 0;
}
