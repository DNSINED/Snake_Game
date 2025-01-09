#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

// Game boundary
const int width = 60;
const int height = 20;


// Color codes
const unsigned short BLUE = 1;
const unsigned short GREEN = 2;
const unsigned short AQUA = 3;
const unsigned short RED = 4;
const unsigned short PURPLE = 5;
const unsigned short YELLOW = 6;
const unsigned short WHITE = 7;
const unsigned short GRAY = 8;
const unsigned short LIGHT_BLUE = 9;
const unsigned short BLACK = 0;
const unsigned short LIGHT_GREEN = 10;
const unsigned short LIGHT_AQUA = 11;
const unsigned short LIGHT_RED = 12;
const unsigned short LIGHT_PURPLE = 13;
const unsigned short LIGHT_YELLOW = 14;
const unsigned short BRIGHT_WHITE = 15;

// Snake and fruit variables
extern int x, y, fruit_x, fruit_y, score;
extern int tail_x[100], tail_y[100];
extern int tail_length;
extern bool game_over;

// Enum to represent the snake's direction
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern Direction dir;

// Function declarations
void Hide_Cursor();
void Set_Console_Colour(int colour);
void Set_Cursor_Position(int x, int y);
void Setup();
void Draw();
void Input();
void Logic();
void Frame_Delay();

#endif // SNAKE_GAME_H
