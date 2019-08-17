#ifndef MAZESOLVER_MAZE_H
#define MAZESOLVER_MAZE_H

#include <set>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<char>> matrix;

class Maze{
public:
    Maze():_maxSteps(0),_numOfRows(0),_numOfCols(0){};
    ~Maze(){ delete(_mazeMap); };
    string _name;
    int _maxSteps;
    int _numOfRows;
    int _numOfCols;
    pair<int, int> _playerStartLocation;
    matrix *_mazeMap;
    matrix* getMap(){return _mazeMap;}
    void initMazeMap();
    void set_playerStartLocation(int x, int y);
    void printMaze(int x,int y,set<pair<int,int>> bk);
    void test_printMazeMap();
};

#endif //MAZESOLVER_MAZE_H
