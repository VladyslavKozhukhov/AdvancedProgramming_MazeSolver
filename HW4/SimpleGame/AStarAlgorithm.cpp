#include "AStarAlgorithm.h"

GameData::Move AStarAlgorithm::getNextMove(GameData::InitData& board,  pair<int,int>& zeroCoordinate){
    Move bestMove;
    unsigned bestHScore = 9;
    unsigned hScore;
    for (auto move: getPossibleMoves(zeroCoordinate)) {
        Board tmpBoard = getBoardAfterMove(board, zeroCoordinate, move);
        hScore = getHScore(tmpBoard);
        if (hScore < bestHScore) {
            bestMove = move;
            bestHScore = hScore;
        }
    }
    return bestMove;
}


Board AStarAlgorithm::getBoardCopy(GameData::InitData& board){
    Board b;
    for(int i=0; i<3; i++){
        for (int j = 0; j < 3; ++j) {
            b.at(i).at(j) = board.get()->at(i).at(j);
        }
    }
    return b;
}

void AStarAlgorithm::swapWithZeroCoordinate(Board &board, pair<int, int> place, pair<int,int>& zeroCoordinate){
    int zeroLocX = zeroCoordinate.first;
    int zeroLocY = zeroCoordinate.second;
    //put number when zero once was
    board.at(zeroLocX).at(zeroLocY) = board.at(place.first).at(place.second);
    //put zero where number once was
    board.at(place.first).at(place.second) = 0;
}

Board AStarAlgorithm::getBoardAfterMove(GameData::InitData& board,pair<int,int>& zeroCoordinate, Move move){
    Board boardCopy  = getBoardCopy(board);
    if(move == GameData::UP){
        swapWithZeroCoordinate(boardCopy, make_pair(zeroCoordinate.first - 1, zeroCoordinate.second), zeroCoordinate);
    }else if(move ==  GameData::DOWN){
        swapWithZeroCoordinate(boardCopy, make_pair(zeroCoordinate.first + 1, zeroCoordinate.second), zeroCoordinate);
    }else if(move ==  GameData::LEFT ){
        swapWithZeroCoordinate(boardCopy, make_pair(zeroCoordinate.first, zeroCoordinate.second - 1), zeroCoordinate);
    }else if(move ==  GameData::RIGHT){
        swapWithZeroCoordinate(boardCopy, make_pair(zeroCoordinate.first, zeroCoordinate.second + 1), zeroCoordinate);
    }
    return boardCopy;
}

unsigned AStarAlgorithm::getHScore(Board& board){
    unsigned score = 0;
    for(unsigned i=0; i<3; i++){
        for(unsigned j=0; j<3; j++){
            if(board.at(i).at(j)!=GameData::winningBoard.at(i).at(j)){
                score++;
            }
        }
    }
    return score;
}