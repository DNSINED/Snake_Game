#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <random>

using namespace std;

// Game boundary
const int width = 80;
const int height = 20;

void Set_Cursor_Position(int x, int y);

// Snake and fruit variables
extern int x, y, fruit_x, fruit_y, score;
extern int tail_x[100], tail_y[100];
extern int tail_length;
extern bool gameOver;

// Enum to represent the snake's direction
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
extern Direction dir;

// Function declarations
void Setup();
void Draw();
void Input();
void Logic();
void Frame_Delay();

#endif // SNAKE_GAME_H
