#include "Algorithm.h"

vector<Move> Algorithm::getPossibleMoves(const pair<int,int>& zeroCoordinate){
    if(zeroCoordinate==make_pair(0,0)){
        return {Move::DOWN,Move::RIGHT};
    }else if(zeroCoordinate==make_pair(0,1)){
        return {Move::DOWN,Move::RIGHT,Move::LEFT};
    }else if(zeroCoordinate==make_pair(0,2)){
        return {Move::DOWN,Move::LEFT};
    }else if(zeroCoordinate==make_pair(1,0)){
        return {Move::UP,Move::DOWN,Move::RIGHT};
    }else if(zeroCoordinate==make_pair(1,1)){
        return {Move::UP,Move::DOWN,Move::RIGHT,Move::LEFT};
    }else if(zeroCoordinate==make_pair(1,2)){
        return {Move::UP,Move::DOWN,Move::LEFT};
    }else if(zeroCoordinate==make_pair(2,0)){
        return {Move::UP,Move::RIGHT};
    }else if(zeroCoordinate==make_pair(2,1)){
        return {Move::UP,Move::LEFT,Move::RIGHT};
    }else if(zeroCoordinate==make_pair(2,2)){
        return {Move::UP,Move::LEFT};
    }
    return {};
}