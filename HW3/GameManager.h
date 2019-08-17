#ifndef MAZESOLVER_GAMEHANDLER_H
#define MAZESOLVER_GAMEHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>
#include "MazeFileParser.h"
#include "AbstractAlgorithm.h"
#include <memory>
#include <algorithm>

using namespace std;


class GameManager {
public:
    GameManager(Maze& maze,const string& outputDir ,const string& algoName,unique_ptr<AbstractAlgorithm> player);
    ~GameManager(){};
    int startGame();
    bool validateMove(pair<int, int> locToCheck,AbstractAlgorithm::Move playerMove,stack<char>* movements,unsigned* numberOfStepsTaken);
    int validateHitWithBookMark(pair<int, int> locToCheck);
    void printPath(stack<char>* movements,bool success);
    void copyPath(stack<char>* movements);
    char convertMovToChar(AbstractAlgorithm::Move move);
    int _numOfThreads;
private:
    Maze& _maze;
    string _outputDir;
    string _algoName;
    unique_ptr<AbstractAlgorithm> _player;
    stack<AbstractAlgorithm::Move> _path;
    set<pair<int,int>> _bookMarkVec;
    pair<int,int> _currentPosition;
    pair<int,int> getNewPlayerCordinates(AbstractAlgorithm::Move move);
    string getOutputFileFullPath();
};

#endif //MAZESOLVER_GAMEHANDLER_H
