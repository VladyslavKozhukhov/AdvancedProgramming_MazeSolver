
#ifndef MAZESOLVER_SECONDSMARTALGORITHM_H
#define MAZESOLVER_SECONDSMARTALGORITHM_H
#include <iostream>
#include <fstream>
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
#include "AbstractAlgorithm.h"
#include <memory>

class SecondSmartAlgorithm;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};
//enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK };

class SecondSmartAlgorithm:public AbstractAlgorithm   {
    class Cell {
        friend SecondSmartAlgorithm;
    public:
        ~Cell();
        Cell(){};
        explicit  Cell(pair<int,int>& curPos):_typeOfCell(Type::UNKOWN),_numOfTied(0),_location(curPos) {}
        pair<int,int> getLocation(){return _location;}
        typename GameData::Move getLastTry(){return _lastTry;}
        void updateCell();
    private:
        Type _typeOfCell;
        int seq =0;
        int _numOfTied = 0;
        pair<int,int> _location;
        typename GameData::Move _lastTry;
        bool _triedDirection[4]; //  DOWN - 0  UP - 1 LEFT - 2  RIGHT -3
    };

public:
    int getId(){return 2;}

    SecondSmartAlgorithm();
    ~SecondSmartAlgorithm();
    typename GameData::Move move();
    void hitWall();
    void hitBookmark(int seq);
    int convertMovToInt();
    typename GameData::Move convertIntToMove(int num);

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
    unique_ptr<stack<Cell>> _path;
    int _xStepToBookMark = 2;
    typename GameData::Move _direction;
    unique_ptr<map<pair<int,int> ,Cell>> _mapPlacementVisit;
    int _counterOfBookMarks;
    int _cols;
    int _rows;

    unique_ptr<Cell> _bookMark;

};


#endif //MAZESOLVER_SECONDSMARTALGORITHM_H
