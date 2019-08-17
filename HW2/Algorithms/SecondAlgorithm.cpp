#include "SecondAlgorithm.h"
#include <ctime>
#include <iostream>
REGISTER_ALGORITHM(SecondAlgorithm)



SecondAlgorithm::Cell::~Cell() {}

SecondAlgorithm::~SecondAlgorithm() {
    delete _path;
    delete _bookMarkVector.front();
    delete _mapPlacementVisit;
}
void SecondAlgorithm::UpdateMove(Cell* mz){
    switch(_direction){
        case Move::DOWN:
            mz->_location.first=mz->_location.first+1;
            mz->_location.second =mz->_location.second;
            updateNewLocation(mz,1);
            break;
        case Move::UP:
            mz->_location.first=mz->_location.first-1;
            mz->_location.second = mz->_location.second;
            updateNewLocation(mz,0);
            break;
        case Move::LEFT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second-1;
            updateNewLocation(mz,3);
            break;
        case  Move::RIGHT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second+1;
            updateNewLocation(mz,2);
            break;
        default:
            break;
    }

}
void SecondAlgorithm::updateNewLocation( Cell* mz,int triedDir){
    auto it = (_mapPlacementVisit->find(mz->_location));
    if(_mapPlacementVisit->find(mz->_location) !=_mapPlacementVisit->end()) {
        it = (_mapPlacementVisit->find(mz->_location));
        *mz = it->second;
    }
    mz->_triedDirection[triedDir]=true;
    mz->_lastTry =  _direction;
    mz->_typeOfCell=Type::SPACE;
    mz->_numOfTied++;
    _currentPos  = mz->_location;
}
SecondAlgorithm::SecondAlgorithm():
        _currentPos(0,0),
        _bookMarked(true),
        _newDir(true),
        _numOfStepsInTheSameDir(0),
        _xStepToBookMark(2)
{
   // std::cout<<"SecondAlgorithm\n"<<endl;
    Cell* _bookMark = new Cell(_currentPos);
    _bookMarkVector.push_back(_bookMark);
    _path = new stack<Cell>();
    Cell mz;
    mz._location = _currentPos;
    mz.updateCell();
    _path->push(mz);
    _mapPlacementVisit = new map<pair<int, int>, Cell>();
    (*_mapPlacementVisit)[_currentPos] = mz;
}
void SecondAlgorithm::Cell::updateCell(){
    _typeOfCell = Type::SPACE;
    _numOfTied = 0;
    _triedDirection[0] = false;
    _triedDirection[1] = false;
    _triedDirection[2] = false;
    _triedDirection[3] = false;
}
void SecondAlgorithm::setBookMark(){
    _bookMarked = true;
    _bookMarkVector.back()->_lastTry=_direction;
    _bookMarkVector.back()->_location = _currentPos;
    _direction = Move::BOOKMARK;
    if (_numOfStepsInTheSameDir >= _xStepToBookMark) {
        _xStepToBookMark = (_xStepToBookMark) * 3;
    }
    _newDir = true;
}

AbstractAlgorithm::Move SecondAlgorithm::move() {
    Cell mz;
    bool dir = false;
    mz.updateCell();
    mz._location = _currentPos;

    if ( _numOfStepsInTheSameDir > _xStepToBookMark ) {
        setBookMark();
        dir = true;
    } else {
        if ((_direction != Move::BOOKMARK || _bookMarked) && !_newDir) {
            if (!validateDir()) {
                if (!chooseNewDirection())
                    _direction = convertIntToMove(rand() % 4);
                _numOfStepsInTheSameDir = 1;
            } else {
                _numOfStepsInTheSameDir++;
                dir = true;
            }
        } else if (_newDir) {
            if (chooseNewDirection()) {
                _numOfStepsInTheSameDir = 1;
                _newDir = false;
                dir = true;
            }
        }
    }
    if(!dir){
        _direction = convertIntToMove(rand() % 4);//stuck
        _numOfStepsInTheSameDir = 1;
    }
    if (_direction != Move::BOOKMARK) {
        UpdateMove(&mz);
        _path->top()._lastTry = _direction;
        _path->top()._triedDirection[convertMovToInt()] = true;
        _path->top()._numOfTied++;
        _path->push(mz);
        (*_mapPlacementVisit)[_currentPos] = mz;
    }
    return _direction;
}

void SecondAlgorithm::hitWall() {
    _path->top()._typeOfCell = Type::WALL;
    (*_mapPlacementVisit)[_currentPos] = _path->top();
    _newDir= true;
    _bookMarked = false;
    undoMove();
}

AbstractAlgorithm::Move SecondAlgorithm::convertIntToMove(int num) {
    switch(num){
        case 0:
            return Move::DOWN;
        case 1:
            return Move::UP;
        case 2:
            return  Move::LEFT;
        case 3:
            return Move::RIGHT;

    }
    return LEFT;//default
}

int SecondAlgorithm::convertMovToInt(){
    switch (_direction){
        case Move::DOWN:
            return 0;
        case Move::UP:
            return 1;
        case Move::LEFT:
            return 2;
        case Move::RIGHT:
            return 3;
        case Move::BOOKMARK:
        default:
            return -1;
    }
}
/**
 * This function validate  direction.
 * The function checks if player can make his next step in this direction by looking on the next
 * cell. If player has visited next cell in this direction it returns false else it returns true. If player has tried
 * all directions it returns true (back trace).
 * @return
 */
bool SecondAlgorithm::validateDir(){
    pair<int,int> tmp = _currentPos;
    bool emptyMap =_mapPlacementVisit->empty();
    if(emptyMap)return true;
    switch (_direction){
        case Move::DOWN:
            tmp.first = tmp.first+1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Move::UP:
            tmp.first = tmp.first-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Move::LEFT:
            tmp.second = tmp.second-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Move::RIGHT:
            tmp.second = tmp.second+1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        default:
            return false;
    }
    Cell currentCell = _path->top();
    auto mzz = _mapPlacementVisit->find(tmp);
    if(mzz->second._numOfTied<4 && mzz->second._typeOfCell!=Type::WALL && currentCell._numOfTied == 4)//backtrace
        return true;
    return false;
}
/**
 * This function chooses new direction to move. Try to Random pick available direction and check it(visited or not)
 * else choose first available direction.
 * @return true or false
 */
bool SecondAlgorithm::chooseNewDirection() {
    vector<int> directionLst;
    for (int j = 0; j < 4; j++) {
        if (!_path->top()._triedDirection[j])
            directionLst.push_back(j);
    }
    srand ( time(NULL) );
    if(directionLst.size()>0 ) {
        switch(directionLst.size()) {
            case 0:
                _direction = convertIntToMove(directionLst[0]);
                break;
            case 1:
                _direction = convertIntToMove(directionLst[1]);
                break;
            case 2:
                _direction = convertIntToMove(directionLst[2]);
                break;
            case 3:
                _direction = convertIntToMove(directionLst[3]);
                break;
            default:
                _direction = convertIntToMove(directionLst[rand() % directionLst.size()]);

        }
    }

    if(validateDir())
        return true;
    for (int j = 0; j < 4; j++) {
        _direction = convertIntToMove(j);
        if (validateDir())
            return true;
    }
    return false;
}
/**
 * Undo last move and update relevant variables.
 */
void SecondAlgorithm::undoMove() {
    Cell mz;
    _direction = _path->top()._lastTry;
    _path->pop();
    if (!_path->empty()) {
        _path->top()._lastTry=_direction;
        _currentPos = _path->top()._location;
    }
}


void SecondAlgorithm::hitBookmark(int seq) {
    if(seq%2==0){//will be improved before tournament
        _newDir = true;
    }
    _xStepToBookMark = 2;
    _numOfStepsInTheSameDir = 0;


}




