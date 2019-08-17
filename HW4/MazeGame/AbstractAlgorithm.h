
#ifndef MAZESOLVER_ABSTRACTALGORITHM_H
#define MAZESOLVER_ABSTRACTALGORITHM_H
#pragma once

#include "GameData.h"

class AbstractAlgorithm {
public:
     ~AbstractAlgorithm(){}
    AbstractAlgorithm(){}

    enum class Type{WALL,SPACE,UNKOWN};

//    enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK };

     virtual GameData::Move move()=0;
     virtual void hitWall() =0;
     virtual void hitBookmark(int seq) =0;
     virtual int getId()=0;
};

#endif //MAZESOLVER_ABSTRACTALGORITHM_H
