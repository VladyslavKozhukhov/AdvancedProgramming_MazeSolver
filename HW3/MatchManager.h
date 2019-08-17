#ifndef MAZESOLVER_MATCHMANAGER_H
#define MAZESOLVER_MATCHMANAGER_H

#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <dlfcn.h>
#include <algorithm>
#include <string>
#include <map>
#include "GameManager.h"
#include "Maze.h"

using namespace std;

class MatchManager {
public:
    mutex _matchMutex;

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
    vector<shared_ptr<Maze>> _mazes;
     string _outputDir;
    static MatchManager* getInstance() ;
    ~MatchManager(){delete _matchManager;}
    void addAlgorithm(function<unique_ptr<AbstractAlgorithm>()>& algorithm) { _registeredAlgorithms.push_back(algorithm); }
    vector<void *> _dlPlayerAlgorithms;
    vector<function<unique_ptr<AbstractAlgorithm>()>> _registeredAlgorithms;
    static void threadRunGameManager();
    atomic<int> _totalNumOfGamesToRun;
    vector<string> _algoNamesLst;
    void startGame(vector<shared_ptr<Maze>> mazes, int numOfThreads, const vector<pair<string,string>>& soFiles, const string& outputDir);
private:
    static MatchManager* _matchManager;
    unique_ptr<Results> _res;
    MatchManager(){};
    vector<string> getMazeNames(vector<shared_ptr<Maze>> mazes);
    vector<string> getAlgorithmNames( const vector<pair<string,string>> &soFiles);
    void openAllDynLibs(const vector<pair<string, string>> &soFiles);
    void closeAllDynLibs();
    void createCompletedGameMatrix(unsigned numOfAlgorithms, vector<string> &mazeNames) const;
    map<string,vector<bool>> _completedGames;
};

#endif //MAZESOLVER_MATCHMANAGER_H
