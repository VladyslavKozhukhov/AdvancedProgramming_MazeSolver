//
// Created by vladko on 6/11/19.
//

#include "Player.h"

GameData::Move Player::move(){
    return _algorithm.move();

}


Player::~Player(){
}

void Player::moveFeedback(GameData::MoveFeedback feedback){
    switch(feedback){
        case GameData::MoveFeedback::HITWALL:
                _algorithm.hitWall();
		break;
        case GameData::MoveFeedback::HITBOOKMARK:
             _algorithm.hitBookmark(0);
		break;
        case GameData::MoveFeedback::RIGHT:
        case GameData::MoveFeedback::DOWN:
        case GameData::MoveFeedback::LEFT:
        case GameData::MoveFeedback::ENDGAME:
        case GameData::MoveFeedback::CONT:
        case GameData::MoveFeedback::UNUSED:
        default:
            break;
    }
}



