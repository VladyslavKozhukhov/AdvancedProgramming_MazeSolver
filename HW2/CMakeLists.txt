cmake_minimum_required(VERSION 3.13)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14 )

include_directories(.)

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
        FirstAlgorithm.cpp
        FirstAlgorithm.h
        README.md AbstractAlgorithm.h AlgorithmRegistration.h SecondAlgorithm.cpp SecondAlgorithm.h AlgorithmRegistration.cpp MatchManager.cpp MatchManager.h)

#target_link_libraries(MazeSolver ${CMAKE_DL_LIBS})
