#include <iostream>
#include "Maze.h"
#define SPACE ' '

void Maze::set_playerStartLocation(int x, int y){
    _playerStartLocation.first = x;
    _playerStartLocation.second = y;
}

void Maze::initMazeMap(){
    _mazeMap = new matrix;
    for(int r=0; r<_numOfRows; r++){
        vector<char> v(_numOfCols,SPACE);
        _mazeMap->push_back(v);
    }
}

void Maze::test_printMazeMap(){ //for debug
    for(int r=0; r<_numOfRows; r++){
        for(int c=0; c<_numOfCols; c++){
            cout<< _mazeMap->at(r).at(c);
        }
        cout<< endl;
    }
}

void Maze::printMaze(int x,int y, set<pair<int,int>> bk) { //for debug
int x_ =0;
int y_ = 0;
    for(auto row = getMap()->begin(); row != getMap()->end(); ++row) {
        y_=0;
        for(auto col = row->begin(); col != row->end(); ++col) {
            if(x==x_ && y == y_){
                cout << "X" <<" ";
            }
            else if (bk.find(std::make_pair(x_,y_)) != bk.end()){
                cout<<"B"<<" ";
            }
            else{
                cout << *col <<" ";
            }
           y_++;
        }
        cout<<endl;
        x_++;

    }
}