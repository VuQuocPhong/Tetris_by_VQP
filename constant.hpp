#ifndef CONSTANT_HPP
#define CONSTANT_HPP
#include <iostream>


const int FILLED = 1;
const int UNFILLED = 0;

const int BOARD_WIDTH = 11;
const int BOARD_HEIGHT = 20;

const int RECTANGLE_SIZE = 35;
const int MAIN_SCREEN_WIDTH = BOARD_WIDTH*RECTANGLE_SIZE;
const int MAIN_SCREEN_HEIGHT = BOARD_HEIGHT*RECTANGLE_SIZE;

const int BLOCK_SIZE = 5;

const int GAME_DELAY_BEAT = 1000;
const int NOTIF_DELAY_TIME = 2000;

const int PLUS_POINT = 10;

const uint8_t PURE_BLACK = 0;
const uint8_t PURE_WHITE = 255;
const int NOTIF_FONT_SIZE = 20;
const std::string FONT_PATH = "arial.ttf";

#endif
