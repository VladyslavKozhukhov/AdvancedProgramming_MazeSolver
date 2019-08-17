//
// Created by vladko on 5/21/19.
//

#ifndef MAZESOLVER_SECONDSMARTALGORITHM_H
#define MAZESOLVER_SECONDSMARTALGORITHM_H
#include "../AbstractAlgorithm.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
#include "../AlgorithmRegistration.h"


class SecondSmartAlgorithm;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};

class SecondSmartAlgorithm: public AbstractAlgorithm  {
    class Cell {
        friend SecondSmartAlgorithm;
    public:
        ~Cell();
        Cell(){};
        explicit  Cell(pair<int,int>& curPos):_typeOfCell(Type::UNKOWN),_numOfTied(0),_location(curPos) {}
        pair<int,int> getLocation(){return _location;}
        Move getLastTry(){return _lastTry;}
        void updateCell();
    private:
        Type _typeOfCell;
        int seq =0;
        int _numOfTied = 0;
        pair<int,int> _location;
        Move _lastTry;
        bool _triedDirection[4]; //  DOWN - 0  UP - 1 LEFT - 2  RIGHT -3
    };

public:
    SecondSmartAlgorithm();
    ~SecondSmartAlgorithm();
    Move move();
    void hitWall();
    void hitBookmark(int seq);
    int convertMovToInt();
    Move convertIntToMove(int num);

private:
    void setBookMark();
    void undoMove();
    bool validateDir();
    void UpdateMove(Cell* mz);
    bool chooseNewDirection();
    void updateNewLocation( Cell* mz,int triedDir);
    void setMazeHeight();
    void setMazeWidth();
private:
    bool _bookMarked;
    bool _knownWidth;
    bool _knownHeight;
    pair<int,int> _currentPos;
    bool _newDir;
    int _numOfStepsInTheSameDir;
    map<int,Cell> _bookMarkIndexMap;
    stack<Cell>* _path;
    int _xStepToBookMark = 2;
    Move _direction;
    map<pair<int,int> ,Cell>* _mapPlacementVisit;
    int _counterOfBookMarks;
    int _cols;
    int _rows;

    Cell *_bookMark;

};


#endif //MAZESOLVER_SECONDSMARTALGORITHM_H
