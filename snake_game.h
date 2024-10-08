#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

// Game boundary
const int width = 80;
const int height = 20;

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
void clrscr();  // Clears the console screen

#endif // SNAKE_GAME_H
