#include "GameManager.h"

bool GameManager::isWinningBoard(GameData::InitData board){
    for(unsigned i=0; i<3;i++){
        for(unsigned j=0; j<3; j++){
            if (board.get()->at(i).at(j)!=GameData::winningBoard.at(i).at(j)){
                return false;
            }
        }
    }
    return true;
}

bool GameManager::endGame(GameData& game, GameData::GameInstanceData& gameInstance) {
    auto currentBoard = game._dynamicBoards.at(gameInstance);
    return isWinningBoard(currentBoard) || (unsigned)game._maxNumOfSteps==game._stepsTaken.at(gameInstance).size();
}

int GameManager::score(GameData& game, GameData::GameInstanceData gameInstance) {
    auto currentBoard = game._dynamicBoards.at(gameInstance);
    if(isWinningBoard(currentBoard)){
        return game._stepsTaken.at(gameInstance).size();
    } else return -1;
}