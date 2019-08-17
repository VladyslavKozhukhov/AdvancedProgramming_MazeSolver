
#include "FirstSmartAlgorithm.h"

#include <ctime>
#include <iostream>


//FirstSmartAlgorithm::~FirstSmartAlgorithm() {
//    delete _path;
//    delete _mapPlacementVisit;
//}

void FirstSmartAlgorithm::UpdateMove(Cell* mz){
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
void FirstSmartAlgorithm::updateNewLocation( Cell* mz,int triedDir){
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

FirstSmartAlgorithm::FirstSmartAlgorithm():
        _currentPos(0,0),
        _newDir(true),
        _numOfStepsInTheSameDir(0),
        _xStepToBookMark(2),
        _counterOfBookMarks(0),
        _cols(0),
        _rows(0),
        _knownWidth(false),
        _knownHeight(false)
{
    //std::cout<<"FirstSmartAlgorithm\n"<<endl;
    _path = make_unique<stack<Cell>>();
    Cell mz;
    mz._location = _currentPos;
    mz.updateCell();
    _path->push(mz);
    _mapPlacementVisit = make_unique<map<pair<int, int>, Cell>>();
    (*_mapPlacementVisit)[_currentPos] = mz;
}


void FirstSmartAlgorithm::Cell::updateCell(){
    _typeOfCell = Type::SPACE;
    _numOfTied = 0;
    _triedDirection[0] = false;
    _triedDirection[1] = false;
    _triedDirection[2] = false;
    _triedDirection[3] = false;
}

void FirstSmartAlgorithm::setBookMark(){
    Cell mz;
    mz.updateCell();
    mz._lastTry=_direction;
    mz._location = _currentPos;
    //_direction = GameData::Move::BOOKMARK;
    _bookMarkIndexMap[_counterOfBookMarks] = mz;

    if (_numOfStepsInTheSameDir >= _xStepToBookMark) {
        _xStepToBookMark = (_xStepToBookMark) * 3;
    }
    //_newDir = true;
}
bool FirstSmartAlgorithm::chooseNewDirection() {
    vector<int> directionLst;
    for (int j = 0; j < 4; j++) {
        if (!_path->top()._triedDirection[j])
            directionLst.push_back(j);
    }
    srand ( time(0) );
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

GameData::Move FirstSmartAlgorithm::move(){
    Cell mz;
    bool dir = false;
    bool visited = true;
    mz.updateCell();
    mz._location = _currentPos;

    if((_knownHeight && _numOfStepsInTheSameDir >= _rows ) || (_knownWidth && _numOfStepsInTheSameDir >= _cols)){
        _newDir = true;
    }
    if ( _numOfStepsInTheSameDir > _xStepToBookMark && !_newDir) {
        setBookMark();
        return GameData::Move::BOOKMARK;
    }

    else {
        if (!_newDir) {
            if (validateDir()) {
                _numOfStepsInTheSameDir++;
                dir = true;
                visited =false;
            }
        }
        if(_newDir || visited){
            if (chooseNewDirection()) {
                _numOfStepsInTheSameDir = 1;
                dir = true;
            }
        }
    }

    if(!dir){
        _direction = convertIntToMove(rand() % 4);//stuck
        _numOfStepsInTheSameDir = 1;
    }

    _newDir = false;

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


void FirstSmartAlgorithm::hitWall() {
    _path->top()._typeOfCell = Type::WALL;
    (*_mapPlacementVisit)[_currentPos] = _path->top();
    _newDir= true;
    undoMove();
}

GameData::Move FirstSmartAlgorithm::convertIntToMove(int num) {
    switch(num){
        case 0:
            return GameData::Move::DOWN;
        case 1:
            return GameData::Move::UP;
        case 2:
            return  GameData::Move::LEFT;
        case 3:
            return GameData::Move::RIGHT;

    }
    return GameData::Move::LEFT;//default
}

int FirstSmartAlgorithm::convertMovToInt(){
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

bool FirstSmartAlgorithm::validateDir(){
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


void FirstSmartAlgorithm::undoMove() {
    Cell mz;
    _direction = _path->top()._lastTry;
    _path->pop();
    if (!_path->empty()) {
        _path->top()._lastTry=_direction;
        _currentPos = _path->top()._location;
    }
}


void FirstSmartAlgorithm::hitBookmark(int seq) {
    Cell mz = _bookMarkIndexMap[seq];

    if(seq == 0 ){
        _numOfStepsInTheSameDir = 0;
        if (mz._lastTry == _direction) {
            if (_direction == GameData::Move::UP || _direction == GameData::Move::DOWN) {
                if (_knownHeight) return;
                _knownHeight = true;
                setMazeHeight(&mz);
            } else {//LEFT RIGHT
                if (_knownWidth) return;
                _knownWidth = true;
                setMazeWidth(&mz);
            }
        }
        _xStepToBookMark = 2;
        _numOfStepsInTheSameDir = 0;
        _newDir = true;

    }
    else if(seq %3 ==0){
        _xStepToBookMark = 2;
        _numOfStepsInTheSameDir = 0;
    } else
        _newDir = true;

}
void FirstSmartAlgorithm::setMazeHeight(Cell* mz){
    _rows = abs(_currentPos.first - mz->_location.first) ;
}
void FirstSmartAlgorithm::setMazeWidth(Cell* mz) {
    _cols = std::abs(_currentPos.second - mz->_location.second);
}
