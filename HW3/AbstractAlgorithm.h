
#ifndef MAZESOLVER_ABSTRACTALGORITHM_H
#define MAZESOLVER_ABSTRACTALGORITHM_H
#pragma once

class AbstractAlgorithm {
public:
    virtual ~AbstractAlgorithm(){}

    enum Move { UP, RIGHT, DOWN, LEFT, BOOKMARK };

    virtual Move move() = 0;
    virtual void hitWall() = 0;
    virtual void hitBookmark(int seq) = 0;
};

#endif //MAZESOLVER_ABSTRACTALGORITHM_H
