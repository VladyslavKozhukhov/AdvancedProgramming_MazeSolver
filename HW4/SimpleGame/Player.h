#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "GameData.h"
#include "Algorithm.h"

typedef GameData::Move Move;
typedef GameData::MoveFeedback Feedback;

class Player {
public:
    //--------------------------
    // required type traits
    //--------------------------
    using Id = std::string;
    //--------------------------
    GameData::InitData _board;
    pair<int,int> _zeroCoordinate;
    Id _playerId;
    int _stepCounter=0;
    Algorithm& _algorithm;
    Player(GameData::InitData board,Id playerId ,Algorithm& algorithm);
    Id id() const { return _playerId; }
    GameData::Move move();
    void moveFeedback(GameData::MoveFeedback feedback);
};

#endif //PLAYER_H
