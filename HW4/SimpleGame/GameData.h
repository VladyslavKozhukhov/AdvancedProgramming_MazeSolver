#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <array>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;
typedef array<array<int, 3>, 3> Board;


class GameData {
public:
    //--------------------------
    // required type traits
    //--------------------------
    using Id = string;
    using GameInstanceData = unsigned ;
    using Move = enum {UP,DOWN,RIGHT,LEFT};
    using MoveFeedback = enum {WIN,MOVED_UP, MOVED_DOWN, MOVED_RIGHT, MOVED_LEFT};
    static const Board winningBoard;
    using InitData = shared_ptr<Board>;
    //--------------------------

    GameInstanceData _instance = 0;
    vector<InitData> _dynamicBoards;
    vector<pair<unsigned ,unsigned >> _currentZeroLocations;
    vector<vector<Move>> _stepsTaken;
    Board _inputBoard;
    Id _gameId;
    int _maxNumOfSteps;
    GameData(Board inputBoard,Id id,int maxNumOfSteps):_inputBoard(inputBoard), _gameId(move(id)),_maxNumOfSteps(maxNumOfSteps){}
    Id id() const { return _gameId; }
    GameInstanceData newGameInstance();
    void moveToZeroLocation(GameData::GameInstanceData instance, pair<unsigned, unsigned> place);
    MoveFeedback processMove(GameData::GameInstanceData instance, GameData::Move move);
    void setInstanceZeroCoordinate(GameInstanceData instance);
};
#endif //GAMEDATA_H
