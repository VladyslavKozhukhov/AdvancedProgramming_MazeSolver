cmake_minimum_required(VERSION 3.13)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14 )
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra  -pedantic-errors -DNDEBUG")
include_directories(.)
set (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl -pthread")


add_executable(MazeSolver
        CMakeLists.txt
        FileHandler.cpp
        FileHandler.h
        GameManager.cpp
        GameManager.h
        main.cpp
        makefile
        Maze.cpp
        Maze.h
        MazeFileParser.cpp
        MazeFileParser.h
        ParserErrorHandler.cpp
        ParserErrorHandler.h
        Algorithms/FirstAlgorithm.cpp
        Algorithms/FirstAlgorithm.h
        README.md AbstractAlgorithm.h AlgorithmRegistration.h Algorithms/SecondAlgorithm.cpp Algorithms/SecondAlgorithm.h AlgorithmRegistration.cpp MatchManager.cpp MatchManager.h Algorithms/FirstSmartAlgorithm.cpp Algorithms/FirstSmartAlgorithm.h Algorithms/SecondSmartAlgorithm.cpp Algorithms/SecondSmartAlgorithm.h)

#target_link_libraries(MazeSolver ${CMAKE_DL_LIBS})
