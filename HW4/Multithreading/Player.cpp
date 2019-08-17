#include "Player.h"

Player::Player(GameData::InitData board, Id playerId, Algorithm& algorithm) : _board(board),_playerId(playerId), _algorithm(algorithm) {
    for (unsigned i = 0; i < 3; i++) {
        for (unsigned j = 0; j < 3; j++) {
            if (board.get()->at(i).at(j) == 0) {
                _zeroCoordinate.first = i;
                _zeroCoordinate.second = j;
            }
        }
    }
}

GameData::Move Player::move(){
    _stepCounter++;
    return _algorithm.getNextMove(_board,_zeroCoordinate);
}

void Player::moveFeedback(GameData::MoveFeedback feedback){
    if(feedback==Feedback::MOVED_UP){
        _zeroCoordinate.first--;
    } else if(feedback==Feedback::MOVED_DOWN){
        _zeroCoordinate.first++;
    }else if(feedback==Feedback::MOVED_LEFT){
        _zeroCoordinate.second--;
    }else if(feedback==Feedback::MOVED_RIGHT){
        _zeroCoordinate.second++;
    }
}