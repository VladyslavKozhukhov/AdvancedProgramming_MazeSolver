cmake_minimum_required(VERSION 3.13)
project(SimpleGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(Multithreading main.cpp Match.h Player.cpp Player.h GameManager.cpp GameManager.h GameData.cpp GameData.h Algorithm.h Algorithm.cpp RandomMovementAlgorithm.cpp RandomMovementAlgorithm.h AStarAlgorithm.cpp AStarAlgorithm.h)