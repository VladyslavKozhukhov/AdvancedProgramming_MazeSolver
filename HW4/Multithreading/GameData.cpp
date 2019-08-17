#include "GameData.h"

const Board GameData::winningBoard = {{{1,2,3},{4,5,6},{7,8,0}}};

GameData::MoveFeedback GameData::processMove(GameData::GameInstanceData instance, GameData::Move move){
    //print for testing
//    cout<< _dynamicBoards.at(instance).get()->at(0).at(0) << _dynamicBoards.at(instance).get()->at(0).at(1) <<_dynamicBoards.at(instance).get()->at(0).at(2) << endl;
//    cout<< _dynamicBoards.at(instance).get()->at(1).at(0) << _dynamicBoards.at(instance).get()->at(1).at(1) <<_dynamicBoards.at(instance).get()->at(1).at(2) << endl;
//    cout<< _dynamicBoards.at(instance).get()->at(2).at(0) << _dynamicBoards.at(instance).get()->at(2).at(1) <<_dynamicBoards.at(instance).get()->at(2).at(2) << endl;
//    cout<<endl;
    //end print
    pair<unsigned ,unsigned> zeroLoc = _currentZeroLocations.at(instance);
    _stepsTaken.at(instance).push_back(move);
    if(move == UP){
        moveToZeroLocation(instance, make_pair(zeroLoc.first - 1, zeroLoc.second));
        return MOVED_UP;
    }else if(move == DOWN){
        moveToZeroLocation(instance, make_pair(zeroLoc.first +1, zeroLoc.second));
        return MOVED_DOWN;
    }else if(move == LEFT ){
        moveToZeroLocation(instance, make_pair(zeroLoc.first , zeroLoc.second-1));
        return MOVED_LEFT;
    }else if(move == RIGHT){
        moveToZeroLocation(instance, make_pair(zeroLoc.first , zeroLoc.second+1));
        return MOVED_RIGHT;
    }
    return WIN;
}

void GameData::moveToZeroLocation(GameData::GameInstanceData instance, pair<unsigned, unsigned> place){
    unsigned zeroLocX = _currentZeroLocations.at(instance).first;
    unsigned zeroLocY = _currentZeroLocations.at(instance).second;
    //put number when zero once was
    _dynamicBoards.at(instance).get()->at(zeroLocX).at(zeroLocY) = _dynamicBoards.at(instance).get()->at(place.first).at(place.second);
    //update zero location
    _currentZeroLocations.at(instance).first = place.first;
    _currentZeroLocations.at(instance).second = place.second;
    //put zero where number once was
    _dynamicBoards.at(instance).get()->at(place.first).at(place.second) = 0;
}

void GameData::setInstanceZeroCoordinate(GameInstanceData instance){
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (_dynamicBoards.at(instance).get()->at(i).at(j) == 0) {
                _currentZeroLocations.push_back(make_pair(i,j));
            }
        }
    }
}

GameData::GameInstanceData GameData::newGameInstance() {
    _dynamicBoards.push_back(make_shared<array<array<int, 3>, 3>>(_inputBoard));
    _stepsTaken.emplace_back(vector<Move>());
    setInstanceZeroCoordinate(_instance);
    return _instance++;
}