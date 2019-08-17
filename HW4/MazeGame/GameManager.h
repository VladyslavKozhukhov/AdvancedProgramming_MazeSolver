//
// Created by vladko on 6/11/19.
//
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "stack"
#include "GameInst.h"
#include "GameData.h"
#ifndef MAZESOLVERMANNAGER_GAMEMANAGER_H
#define MAZESOLVERMANNAGER_GAMEMANAGER_H

class GameManager {
public:
    GameData::InitData getInitData(GameData &game, GameData::GameInstanceData &gameInstance) {
        if(game._outputDir=="" && gameInstance.getAlgoName()!="")
            return 0;
        else return 1;
    }

    GameData::MoveFeedback processMove(GameData &game, GameData::GameInstanceData &gameInstance, GameData::Move move){
        if(game._id != "-1")
            return gameInstance.procc(move);
        else{
            return gameInstance.procc(move);

        }

    }
    //return game.processMove(gameInstance, move);



    bool endGame(GameData& game, GameData::GameInstanceData& gameInstance) {
        if(game._id!="-1") {
            return gameInstance.getTotalWin();
        }
        return false;
    }
    int score(GameData& game, GameData::GameInstanceData& gameInstance) {
        if(game._id!="-1") {
            return gameInstance.getScore();
        }
        return -1;
    }
//    pair<int, int> getNewPlayerCordinates(GameData::Move move);
//    int validateHitWithBookMark(pair<int, int> locToCheck);
//    bool validateMove(pair<int, int> locToCheck, GameData::Move playerMove, stack<char> *movements,unsigned *numberOfStepsTaken);


};

#endif //MAZESOLVERMANNAGER_GAMEMANAGER_H
