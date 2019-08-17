#ifndef MAZESOLVER_GAMEHANDLER_H
#define MAZESOLVER_GAMEHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "Player.h"


using namespace std;


class GameManager {
public:
    GameManager(Maze& maze, ofstream& outputFileStream);
    void startGame();
    void printPath(stack<char>* movements,bool success);
    ~GameManager(){};
    void copyPath(stack<Cell>* path,stack<char>* movements);
private:
    Maze& _maze;
    pair<int,int> _currentPosition;
    ofstream& _outputStream;
    pair<int,int> getNewPlayerCordinates(Movement move);
};

#endif //MAZESOLVER_GAMEHANDLER_H
