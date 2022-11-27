cmake_minimum_required(VERSION 3.23)
project(Hex_Game)

set(CMAKE_CXX_STANDARD 23)

add_executable(Hex_Game main.cpp Game.cpp Game.h Player.cpp Player.h)
