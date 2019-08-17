
#include "SecondSmartAlgorithm.h"

#include <ctime>
#include <iostream>


SecondSmartAlgorithm::Cell::~Cell() {

}

SecondSmartAlgorithm::~SecondSmartAlgorithm() {
//    delete _path;
//    delete _mapPlacementVisit;
   // delete _bookMark;
}



void SecondSmartAlgorithm::UpdateMove(Cell* mz){
    switch(_direction){
        case GameData::Move::DOWN:
            mz->_location.first=mz->_location.first+1;
            mz->_location.second =mz->_location.second;
            updateNewLocation(mz,1);
            break;
        case GameData::Move::UP:
            mz->_location.first=mz->_location.first-1;
            mz->_location.second = mz->_location.second;
            updateNewLocation(mz,0);
            break;
        case GameData::Move::LEFT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second-1;
            updateNewLocation(mz,3);
            break;
        case  GameData::Move::RIGHT:
            mz->_location.first=mz->_location.first;
            mz->_location.second =mz->_location.second+1;
            updateNewLocation(mz,2);
            break;
        default:
            break;
    }

}
void SecondSmartAlgorithm::updateNewLocation( Cell* mz,int triedDir){
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
SecondSmartAlgorithm::SecondSmartAlgorithm():
        _bookMarked(true),
        _knownWidth(false),
        _knownHeight(false),
        _currentPos(0,0),
        _newDir(true),
        _numOfStepsInTheSameDir(0),
        _xStepToBookMark(3),
        _cols(-1),
        _rows(-1)
{
    _path = make_unique<stack<Cell>>();
    Cell mz;
    mz._location = _currentPos;
    mz.updateCell();
    _bookMark = make_unique<Cell>(_currentPos);
    _path->push(mz);
    _mapPlacementVisit = make_unique<map<pair<int, int>, Cell>>();
    (*_mapPlacementVisit)[_currentPos] = mz;
}
void SecondSmartAlgorithm::Cell::updateCell(){

        _typeOfCell = Type::SPACE;
    _numOfTied = 0;
    _triedDirection[0] = false;
    _triedDirection[1] = false;
    _triedDirection[2] = false;
    _triedDirection[3] = false;
}
void SecondSmartAlgorithm::setBookMark(){
    _direction = GameData::Move::BOOKMARK;
    Cell mz;
    _bookMarked = true;
    mz.updateCell();
    mz._lastTry=_direction;
    mz._location = _currentPos;
    mz._triedDirection[convertMovToInt()]=true;

    _bookMarkIndexMap[_counterOfBookMarks] = mz;
    _bookMark->_lastTry=_direction;
    _bookMark->_location = _currentPos;
    _bookMark->_triedDirection[convertMovToInt()]=true;
    _bookMark->seq= _counterOfBookMarks;
    _counterOfBookMarks++;
    if (_numOfStepsInTheSameDir > _xStepToBookMark) {
          _xStepToBookMark = 9;
        _numOfStepsInTheSameDir = 0;
    }
    _newDir = true;
}
/**
 * This function compute the next move of the SecondSmartAlgorithm. SecondSmartAlgorithm prefers to move in the same direction until
 * he meets wall/bookmark/place that he has visited yet. After meeting with wall SecondSmartAlgorithm puts bookmark and
 * chooses new direction. In the case of meeting with bookmark/old place he chooses new direction.
 * Straight after SecondSmartAlgorithm finds out height or width of the maze he will change his direction after
 * every height/width steps.
 * @return
 */
    GameData::Move SecondSmartAlgorithm::move(){
    Cell mz;
    bool dir = false;
    mz.updateCell();
    mz._location = _currentPos;
   // cout<<"LOCATION _______________________ " <<_currentPos.first<<"| "<<_currentPos.second<<endl;
    if((_knownHeight && _numOfStepsInTheSameDir >= _rows ) || (_knownWidth && _numOfStepsInTheSameDir >= _cols)){
        _newDir = true;
    }
    if ( _numOfStepsInTheSameDir > _xStepToBookMark ) {
        setBookMark();
        dir = true;
    } else {
        if ((_direction != GameData::Move::BOOKMARK || _bookMarked) && !_newDir) {
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
    if (_direction != GameData::Move::BOOKMARK) {
        UpdateMove(&mz);
        _path->top()._lastTry = _direction;
        _path->top()._triedDirection[convertMovToInt()] = true;
        _path->top()._numOfTied++;
        _path->push(mz);
        (*_mapPlacementVisit)[_currentPos] = mz;
    }
    return _direction;
}

void SecondSmartAlgorithm::hitWall() {
    _path->top()._typeOfCell = Type::WALL;
    (*_mapPlacementVisit)[_currentPos] = _path->top();
    _newDir= true;
    _bookMarked = false;
    undoMove();
}

GameData::Move  SecondSmartAlgorithm::convertIntToMove(int num) {
    switch(num){
        case 0:
            return GameData::Move::DOWN;
        case 1:
            return GameData::Move::UP;
        case 2:
            return  GameData::Move::LEFT;
        case 3:
            return GameData::Move::RIGHT;
        default:
            return GameData::Move::DOWN;

    }
}

int SecondSmartAlgorithm::convertMovToInt(){
    switch (_direction){
        case GameData::Move::DOWN:
            return 0;
        case GameData::Move::UP:
            return 1;
        case GameData::Move::LEFT:
            return 2;
        case GameData::Move::RIGHT:
            return 3;
        case GameData::Move::BOOKMARK:
        default:
            return -1;
    }
}
/**
 * This function validate  direction.
 * The function checks if SecondSmartAlgorithm can make his next step in this direction by looking on the next
 * cell. If SecondSmartAlgorithm has visited next cell in this direction it returns false else it returns true. If SecondSmartAlgorithm has tried
 * all directions it returns true (back trace).
 * @return
 */
bool SecondSmartAlgorithm::validateDir(){
    pair<int,int> tmp = _currentPos;
    bool emptyMap =_mapPlacementVisit->empty();
    if(emptyMap)return true;
    switch (_direction){
        case GameData::Move::DOWN:
            tmp.first = tmp.first+1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case GameData::Move::UP:
            tmp.first = tmp.first-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case GameData::Move::LEFT:
            tmp.second = tmp.second-1;
            if(_mapPlacementVisit->find(tmp) ==_mapPlacementVisit->end())
                return true;
            break;
        case GameData::Move::RIGHT:
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
bool SecondSmartAlgorithm::chooseNewDirection() {
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
void SecondSmartAlgorithm::undoMove() {
    Cell mz;
    _direction = _path->top()._lastTry;
    _path->pop();
    if (!_path->empty()) {
        _path->top()._lastTry=_direction;
        _currentPos = _path->top()._location;
    }
}

/**
 * This function can compute height or width of the maze
 */
void SecondSmartAlgorithm::hitBookmark(int seq) {
    Cell mz = _bookMarkIndexMap[seq];
    mz._triedDirection[convertMovToInt()]=true;
    _bookMarkIndexMap[seq]=mz;
    Cell mzz = _path->top();
    mzz._triedDirection[0] = mz._triedDirection[0];
    mzz._triedDirection[1] = mz._triedDirection[1];
    mzz._triedDirection[2] = mz._triedDirection[2];
    mzz._triedDirection[3] = mz._triedDirection[3];
    _path->pop();
    _path->push(mzz);
//    _newDir = true;
//    _xStepToBookMark = 3;
//    _numOfStepsInTheSameDir = 0;

    _newDir = true;
    _xStepToBookMark = 2;
    _numOfStepsInTheSameDir = 0;
    if (_bookMark->_lastTry == _direction && _bookMark->seq ==seq) {
        if (_direction == GameData::Move::UP || _direction == GameData::Move::DOWN) {
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



void SecondSmartAlgorithm::setMazeHeight(){
    _rows = abs(_currentPos.first - _bookMark->_location.first) ;
}
void SecondSmartAlgorithm::setMazeWidth() {
    _cols = std::abs(_currentPos.second - _bookMark->_location.second);
}