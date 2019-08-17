cmake_minimum_required(VERSION 3.13)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MazeSolver
        .idea/encodings.xml
        .idea/MazeSolver.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/workspace.xml
        tests/GoodMazeWithNoSol.txt
        tests/GoodMazeWithNoSol_output.txt
        tests/maze1.in
        tests/maze1.out
        tests/maze2.in
        tests/maze2.out
        tests/maze3.in
        tests/maze4.in
        tests/maze5.in
        tests/MorePlayersNoExit.txt
        tests/No_Player.txt
        tests/output_to_screen.txt
        tests/Row_Issue.txt
        tests/simple_maze_1.in
        tests/simple_maze_2.in
        tests/simple_test_1.out
        tests/temp.out
        tests/TEST1_BadChar.txt
        tests/TEST1_BadChar_output.txt
        tests/TEST2_Cols_Issue.txt
        tests/TEST2_Cols_Issue_output.txt
        tests/TEST2_FAIL_BadChar.in
        tests/test5.txt
        .gitignore
        CMakeLists.txt
        FileHandler.cpp
        FileHandler.h
        GameManager.cpp
        GameManager.h
        main.cpp
        makefile
        Maze.cpp
        Maze.h
        Parser.cpp
        Parser.h
        ParserErrorHandler.cpp
        ParserErrorHandler.h
        Player.cpp
        Player.h
        README.md)
