#ifndef A_STAR_ALGORITHM_H
#define A_STAR_ALGORITHM_H
#include "Algorithm.h"

class AStarAlgorithm:public Algorithm{
private:
    Board getBoardCopy(GameData::InitData& board);
    void swapWithZeroCoordinate(Board &board, pair<int, int> place, pair<int,int>& zeroCoordinate);
    Board getBoardAfterMove(GameData::InitData& board,pair<int,int>& zeroCoordinate, Move move);
    unsigned getHScore(Board& board);
public:
    GameData::Move getNextMove(GameData::InitData& board,  pair<int,int>& zeroCoordinate);
};

#endif //A_STAR_ALGORITHM_H
