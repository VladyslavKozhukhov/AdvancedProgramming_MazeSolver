#ifndef MAZESOLVER_PLAYER_H
#define MAZESOLVER_PLAYER_H
#include <utility>
#include <stack>
#include <map>
#include <list>
#include <random>
class Player;
class Cell;
using namespace std;
enum class Type{WALL,SPACE,UNKOWN};
enum class Movement{UP='U', DOWN='D', RIGHT='R',LEFT='L', BOOKMARK,UNDEF};
typedef map<pair<int,int> ,Cell>  mapPlaceVisit;

class Cell {
    friend Player;
public:
    ~Cell();
    Cell(){};
    explicit  Cell(pair<int,int>& curPos):_typeOfCell(Type::UNKOWN),_numOfTied(0),_location(curPos),_lastTry(Movement::UNDEF) {}
    pair<int,int> getLocation(){return _location;}
    Movement getLastTry(){return _lastTry;}
    void updateCell();
private:
    Type _typeOfCell;
    int _numOfTied = 0;
    pair<int,int> _location;
    Movement _lastTry;//print to file
    bool _triedDirection[4]; // 0 DOWN UP1 2LEFT 3RIGHT
};

class Player {
public:
    Player();
    ~Player();
    Movement move();
    void hitWall();
    void hitBookmark();
    pair<int,int> getBookMark(){return _bookMark->getLocation();}
    stack<Cell>* getPath(){return _path;}
private:
    void setBookMark();
    void undoMove();
    bool validateDir();
    void UpdateMove(Cell* mz);
    bool chooseNewDirection();
    int convertMovToInt();
    Movement convertIntToMove(int num);
    void setMazeHeight();
    void setMazeWidth();
    void updateNewLocation( Cell* mz,int triedDir);
private:
    bool _knownWidth;
    bool _knownHeight;
    pair<int,int> _currentPos;
    bool _bookMarked;
    bool _newDir;
    int _numOfStepsInTheSameDir;
    int _xStepToBookMark;
    int _cols;
    int _rows;
    stack<Cell>* _path;
    Cell* _bookMark;
    Movement _direction;
    mapPlaceVisit * _mapPlacementVisit;

};


#endif //MAZESOLVER_PLAYER_H
