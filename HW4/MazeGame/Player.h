#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "GameData.h"
#include "FirstSmartAlgorithm.h"
#include "SecondSmartAlgorithm.h"
#include <functional>
#include <memory>

#ifndef MAZESOLVERMANNAGER_PLAYER_H
#define MAZESOLVERMANNAGER_PLAYER_H


class Player {
public:
//    std::function<void(void)> algorithm;
//    AbstractAlgorithm* _algorithm;
    AbstractAlgorithm& _algorithm;

    //--------------------------
    // required type traits
    //--------------------------
    using Id = int;
    //--------------------------

    Player(GameData::InitData,AbstractAlgorithm& func):_algorithm(func){
    }
    Id id() const { return _algorithm.getId() ; }
    GameData::Move move();// { return GameData::Move{}; }
    void moveFeedback(GameData::MoveFeedback feedback);
    FirstSmartAlgorithm* _firstSmartAlgo=nullptr;
    SecondSmartAlgorithm* _secondSmartAlgo =  nullptr;
    ~Player();
};

#endif //MAZESOLVERMANNAGER_PLAYER_H
