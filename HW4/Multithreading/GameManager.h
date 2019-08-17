
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameData.h"

class GameManager {
public:
    GameData::InitData getInitData(GameData& game, GameData::GameInstanceData gameInstance) {
        return game._dynamicBoards.at(gameInstance);
    }
    GameData::MoveFeedback processMove(GameData& game, GameData::GameInstanceData gameInstance, GameData::Move move) {
        return game.processMove(gameInstance, move);
    }

    bool isWinningBoard(GameData::InitData board);

    bool endGame(GameData& game, GameData::GameInstanceData& gameInstance);

    int score(GameData& game, GameData::GameInstanceData gameInstance);
};
#endif //GAMEMANAGER_H
