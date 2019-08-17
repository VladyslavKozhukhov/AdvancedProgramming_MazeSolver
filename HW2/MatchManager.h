#ifndef MAZESOLVER_MATCHMANAGER_H
#define MAZESOLVER_MATCHMANAGER_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>

#include <atomic>
#include <dlfcn.h>
#include <algorithm>
#include <string>
#include "GameManager.h"
#include "Maze.h"

using namespace std;

class MatchManager {
public:
    class Results {
    public:
        Results(const vector<string>& mazeNames,const vector<string>& algoNames);
        ~Results();
        void add(string mazeName, string algoName, int numOfSteps);
        void print();
    private:
        int getLongestStringSize(const vector<string> &vec);
        vector<string> _mazeNames;
        vector<string> _algoNames;
        int **_stepsTaken;
        int getMazeNameIndex(const string& mazeName);
        int getAlgoNameIndex(const string& algoName);
        int getCellWidth();
    };
    static MatchManager* getInstance() ;
    ~MatchManager(){delete _matchManager;}
    void addAlgorithm(function<unique_ptr<AbstractAlgorithm>()>& algorithm) { _algorithms.push_back(algorithm); }
    void startGame(const vector<Maze*>& mazes,const vector<pair<string,string>>& soFiles, const string& outputDir);
    void closeDll();
    vector<void *> _dlPlayerAlgorithms;
    vector<function<unique_ptr<AbstractAlgorithm>()>> _algorithms;
private:
    static MatchManager* _matchManager;
    MatchManager(){};
    vector<string> getMazeNames(const vector<Maze *> &mazes);
    vector<string> getAlgorithmNames( const vector<pair<string,string>> &soFiles);
};

#endif //MAZESOLVER_MATCHMANAGER_H
