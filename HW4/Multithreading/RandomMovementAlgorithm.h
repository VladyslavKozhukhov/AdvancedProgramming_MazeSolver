#ifndef RANDOM_MOVEMENT_ALGORITHM_H
#define RANDOM_MOVEMENT_ALGORITHM_H

#include <ctime>
#include "Algorithm.h"

class RandomMovementAlgorithm:public Algorithm{
public:
    RandomMovementAlgorithm(){ srand(time(nullptr));};
    GameData::Move getNextMove(GameData::InitData& board,  pair<int,int>& zeroCoordinate);
};

#endif //RANDOM_MOVEMENT_ALGORITHM_H
