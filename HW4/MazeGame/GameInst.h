//
// Created by vladko on 6/12/19.
//
#include "Maze.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <set>
#include <memory>
#include <algorithm>
#ifndef MAZESOLVERMANNAGER_GAMEINST_H
#define MAZESOLVERMANNAGER_GAMEINST_H
//#define END '$'
//#define WALL  '#'
//#define SPACE ' '
//#define PLAYER '@'

class GameInst {
public:
    GameInst();
    static string turn ;
    enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK,HITWALL,HITBOOKMARK ,ENDGAME,CONT,UNUSED};

    int validateHitWithBookMark(pair<int, int> locToCheck);

    Move  validateMove(pair<int, int> locToCheck, Move playerMove, stack<char> *movements,
                      unsigned *numberOfStepsTaken);
    GameInst::Move  procc(Move playerMove);

    pair<int, int> getNewPlayerCordinates(Move move);

    int score();

    GameInst(Maze& maze,const string& outputDir ,const string& algoName);
    ~GameInst(){delete movements;};
    int startGame();
    void printPath(stack<char>* movements,bool success);
    void copyPath(stack<char>* movements);
    char convertMovToChar( Move move);
    bool getTotalWin();
    int getScore();
    string getAlgoName(){return _algoName;}
private:
    Maze& _maze;
    string _outputDir;
    string _algoName;
    stack< Move> _path;
    set<pair<int,int>> _bookMarkVec;
    pair<int,int> _currentPosition;
    string getOutputFileFullPath();
    bool winGameTotal ;
    Move winGame ;
    unsigned numberOfStepsTaken = _maze._maxSteps ;
    stack<char> *movements;
    int steps;
    int numOfTries;
    int index;
    bool endGame = false;
//    string _algoNum;

};
#endif //MAZESOLVERMANNAGER_GAMEINST_H
