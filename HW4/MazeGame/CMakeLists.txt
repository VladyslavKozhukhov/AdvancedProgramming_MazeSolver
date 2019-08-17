cmake_minimum_required(VERSION 3.14)
project(HW4)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW4 Match.cpp SecondSmartAlgorithm.h SecondSmartAlgorithm.cpp Player.h Player.cpp ParserErrorHandler.h ParserErrorHandler.cpp MazeFileParser.h MazeFileParser.cpp Maze.h Maze.cpp Match.h GameInst.h GameManager.cpp GameManager.h GameInst.cpp GameData.h GameData.cpp FirstSmartAlgorithm.h FirstSmartAlgorithm.cpp FileHandler.h FileHandler.cpp AbstractAlgorithm.h main.cpp)