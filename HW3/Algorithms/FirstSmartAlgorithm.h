#ifndef MAZESOLVER_FIRSTSMARTALGORITHM_H
#define MAZESOLVER_FIRSTSMARTALGORITHM_H
#include "../AbstractAlgorithm.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
#include "../AlgorithmRegistration.h"

class FirstSmartAlgorithm;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};

class FirstSmartAlgorithm: public AbstractAlgorithm  {

    class Cell {
        friend FirstSmartAlgorithm;
    public:
        ~Cell();
        Cell(){};
        explicit  Cell(pair<int,int>& curPos):_typeOfCell(Type::UNKOWN),_numOfTied(0),_location(curPos) {}
        pair<int,int> getLocation(){return _location;}
        Move getLastTry(){return _lastTry;}
        void updateCell();
    private:
        Type _typeOfCell;
        int _numOfTied = 0;
        pair<int,int> _location;
        Move _lastTry;
        bool _triedDirection[4]; //  DOWN - 0  UP - 1 LEFT - 2  RIGHT -3
    };

public:
    FirstSmartAlgorithm();
    ~FirstSmartAlgorithm();
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
    void setMazeHeight(Cell* mz);
    void setMazeWidth(Cell* mz);
private:
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
    bool _knownWidth;
    bool _knownHeight;

};




#endif //MAZESOLVER_FIRSTSMARTALGORITHM_H
