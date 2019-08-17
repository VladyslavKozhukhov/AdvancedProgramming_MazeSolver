#ifndef MAZESOLVER_PLAYER_H
#define MAZESOLVER_PLAYER_H
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
#include "../AlgorithmRegistration.h"
#include "../AbstractAlgorithm.h"

class FirstAlgorithm;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};
//enum class Move{UP='U', DOWN='D', RIGHT='R',LEFT='L', BOOKMARK,UNDEF};

class FirstAlgorithm: public AbstractAlgorithm  {
public:
    FirstAlgorithm();
    ~FirstAlgorithm();
    Move move();
    // AbstractAlgorithm::Move  moveT(){return AbstractAlgorithm::DOWN;};
    void hitWall();
    void hitBookmark(int seq);
    pair<int,int> getBookMark(){return _bookMark->getLocation();}
    class Cell {
        friend FirstAlgorithm;
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
    void setMazeHeight();
    void setMazeWidth();
    void updateNewLocation( Cell* mz,int triedDir);
private:

    pair<int,int> _currentPos;
    bool _bookMarked;
    bool _newDir;
    int _numOfStepsInTheSameDir;
    int _xStepToBookMark;
    int _cols;
    int _rows;
    bool _knownWidth;
    bool _knownHeight;
    stack<Cell>* _path;
    Cell* _bookMark;
    Move _direction;
    map<pair<int,int> ,Cell>* _mapPlacementVisit;

};



#endif //MAZESOLVER_PLAYER_H
