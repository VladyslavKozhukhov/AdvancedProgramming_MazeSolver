#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "GameData.h"

typedef GameData::Move Move;

class Algorithm {
public:
    virtual ~Algorithm() {};
    virtual Move getNextMove(GameData::InitData& board,  pair<int,int>& zeroCoordinate) =0;
protected:
    vector<Move> getPossibleMoves(const pair<int,int>& zeroCoordinate);
};

#endif //ALGORITHM_H
