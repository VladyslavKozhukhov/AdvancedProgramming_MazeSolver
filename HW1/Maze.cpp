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

void Maze::printMaze(int x,int y, pair<int,int>& bk) { //for debug
    int xB = bk.first;
    int yB = bk.second;
    for(auto row = getMap()->begin(); row != getMap()->end(); ++row) {
        for(auto col = row->begin(); col != row->end(); ++col) {
            if(x==0 && y == 0){
                cout << "X" <<" ";
            }
            else if (yB ==0 &&xB == 0){
                cout<<"B"<<" ";
            }
            else{
                cout << *col <<" ";
            }
            if(x==0)
                y--;
            if(xB ==0)
                yB--;
        }
        cout<<endl;
        x--;
        xB--;
    }
}