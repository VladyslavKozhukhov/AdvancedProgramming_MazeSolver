#ifndef MAZESOLVER_RANDOMALGORITHM_H
#define MAZESOLVER_RANDOMALGORITHM_H

#include "AbstractAlgorithm.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
#include "AlgorithmRegistration.h"

class TAlgorithm;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};
//enum class Move{UP='U', DOWN='D', RIGHT='R',LEFT='L', BOOKMARK,UNDEF};

class TAlgorithm: public AbstractAlgorithm  {
public:
    TAlgorithm();
    ~TAlgorithm();
    Move move();
    // AbstractAlgorithm::Move  moveT(){return AbstractAlgorithm::DOWN;};
    void hitWall();
    void hitBookmark(int seq);
    class Cell {
        friend TAlgorithm;
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
        Move _lastTry;//print to file
        bool _triedDirection[4]; // 0 DOWN UP1 2LEFT 3RIGHT
    };

private:
    void setBookMark();
    void undoMove();
    bool validateDir();
    void UpdateMove(Cell* mz);
    bool chooseNewDirection();
    int convertMovToInt();
    Move convertIntToMove(int num);

    void updateNewLocation( Cell* mz,int triedDir);
private:

    pair<int,int> _currentPos;
    bool _bookMarked;
    bool _newDir;
    int _numOfStepsInTheSameDir;
    int _xStepToBookMark;

    stack<Cell>* _path;
    vector<Cell*> _bookMarkVector;
    Move _direction;
    map<pair<int,int> ,Cell>* _mapPlacementVisit;

};




#endif //MAZESOLVER_RANDOMALGORITHM_H
