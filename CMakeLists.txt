cmake_minimum_required(VERSION 3.28)
project(snake_game)

set(CMAKE_CXX_STANDARD 26)

add_executable(snake_game snake_game.cpp
        snake_game.h
        cls.h)
