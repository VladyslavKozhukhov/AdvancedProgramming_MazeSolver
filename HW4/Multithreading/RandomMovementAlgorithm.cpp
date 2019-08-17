#include "RandomMovementAlgorithm.h"

GameData::Move RandomMovementAlgorithm::getNextMove(GameData::InitData& board,  pair<int,int>& zeroCoordinate){
    auto moves = getPossibleMoves(zeroCoordinate);
    return moves.at((rand()+board.get()->size())%moves.size());
}
