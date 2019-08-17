#include "Player.h"
#include <ctime>
#include <iostream>



Cell::~Cell() {}

Player::~Player() {
    delete _path;
    delete _bookMark;
    delete _mapPlacementVisit;
}
void Player::UpdateMove(Cell* mz){
    switch(_direction){
        case Movement::DOWN:
            mz->_location.first=mz->_location.first+1;
            mz->_location.second =mz->_location.second;
            updateNewLocation(mz,1);
            break;
        case Movement::UP:
            mz->_location.first=mz->_location.first-1;
            mz->_location.second = mz->_location.second;
            updateNewLocation(mz,0);
            break;
        case Movement::LEFT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second-1;
            updateNewLocation(mz,3);
            break;
        case  Movement::RIGHT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second+1;
            updateNewLocation(mz,2);
            break;
        default:
            break;
    }

}
void Player::updateNewLocation( Cell* mz,int triedDir){
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
Player::Player():
    _knownWidth(false),
    _knownHeight(false),
    _currentPos(0,0),
    _bookMarked(true),
    _newDir(true),
     _numOfStepsInTheSameDir(0),
     _xStepToBookMark(2),
     _cols(-1),
     _rows(-1)
{
    _bookMark = new Cell(_currentPos);
    _path = new stack<Cell>();
    Cell mz;
    mz._location = _currentPos;
    mz.updateCell();
    _path->push(mz);
    _mapPlacementVisit = new map<pair<int, int>, Cell>();
    (*_mapPlacementVisit)[_currentPos] = mz;
}
void Cell::updateCell(){
    _typeOfCell = Type::SPACE;
    _numOfTied = 0;
    _triedDirection[0] = false;
    _triedDirection[1] = false;
    _triedDirection[2] = false;
    _triedDirection[3] = false;
}
void Player::setBookMark(){
    _bookMarked = true;
    _bookMark->_lastTry=_direction;
    _bookMark->_location = _currentPos;
    _direction = Movement::BOOKMARK;
    if (_numOfStepsInTheSameDir >= _xStepToBookMark) {
        _xStepToBookMark = (_xStepToBookMark) * 2;
    }
    _newDir = true;
}
/**
 * This function compute the next move of the player. Player prefers to move in the same direction until
 * he meets wall/bookmark/place that he has visited yet. After meeting with wall player puts bookmark and
 * chooses new direction. In the case of meeting with bookmark/old place he chooses new direction.
 * Straight after player finds out height or width of the maze he will change his direction after
 * every height/width steps.
 * @return
 */
Movement Player::move() {
    Cell mz;
    bool dir = false;
    mz.updateCell();
    mz._location = _currentPos;
    if((_knownHeight && _numOfStepsInTheSameDir >= _rows ) || (_knownWidth && _numOfStepsInTheSameDir >= _cols)){
        _newDir = true;
    }
    if ( _numOfStepsInTheSameDir > _xStepToBookMark ) {
        setBookMark();
        dir = true;
    } else {
        if ((_direction != Movement::BOOKMARK || _bookMarked) && !_newDir) {
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
    if (_direction != Movement::BOOKMARK) {
        UpdateMove(&mz);
        _path->top()._lastTry = _direction;
        _path->top()._triedDirection[convertMovToInt()] = true;
        _path->top()._numOfTied++;
        _path->push(mz);
        (*_mapPlacementVisit)[_currentPos] = mz;
    }
    return _direction;
}

void Player::hitWall() {
    _path->top()._typeOfCell = Type::WALL;
    (*_mapPlacementVisit)[_currentPos] = _path->top();
    _newDir= true;
    _bookMarked = false;
    undoMove();
}

Movement Player::convertIntToMove(int num) {
    switch(num){
        case 0:
             return Movement::DOWN;
        case 1:
            return Movement::UP;
        case 2:
            return  Movement::LEFT;
        case 3:
            return Movement::RIGHT;
        default:
            return Movement::UNDEF;
    }
}

int Player::convertMovToInt(){
    switch (_direction){
        case Movement::DOWN:
            return 0;
        case Movement::UP:
            return 1;
        case Movement::LEFT:
            return 2;
        case Movement::RIGHT:
            return 3;
        case Movement::BOOKMARK:
        case Movement::UNDEF:
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
bool Player::validateDir(){
    pair<int,int> tmp = _currentPos;
    bool emptyMap =_mapPlacementVisit->empty();
    if(emptyMap)return true;
    switch (_direction){
        case Movement::DOWN:
            tmp.first = tmp.first+1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Movement::UP:
            tmp.first = tmp.first-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Movement::LEFT:
            tmp.second = tmp.second-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case Movement::RIGHT:
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
bool Player::chooseNewDirection() {
    vector<int> directionLst;
    for (int j = 0; j < 4; j++) {
        if (!_path->top()._triedDirection[j])
            directionLst.push_back(j);
    }
    srand ( time(NULL) );
    if(directionLst.size()>0 )
        _direction = convertIntToMove(directionLst[rand()%directionLst.size()]);
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
void Player::undoMove() {
    Cell mz;
    _direction = _path->top()._lastTry;
    _path->pop();
    if (!_path->empty()) {
        _path->top()._lastTry=_direction;
        _currentPos = _path->top()._location;
    }
}

void Player::setMazeHeight(){
    _rows = abs(_currentPos.first - _bookMark->_location.first) ;
}
void Player::setMazeWidth() {
    _cols = std::abs(_currentPos.second - _bookMark->_location.second);
}
/**
 * This function can compute height or width of the maze
 */
void Player::hitBookmark() {
    _newDir = true;
    _xStepToBookMark = 2;
    _numOfStepsInTheSameDir = 0;
    if (_bookMark->_lastTry == _direction) {
        if (_direction == Movement::UP || _direction == Movement::DOWN) {
            if (_knownHeight) return;
            _knownHeight = true;
            setMazeHeight();
        } else {//LEFT RIGHT
            if (_knownWidth) return;
            _knownWidth = true;
            setMazeWidth();
        }
    }

}




