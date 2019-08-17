#include "MatchManager.h"
#include "MatchManager.h"
#include <algorithm>
#include <sstream>
#include <cstring>
#include <iomanip>

#define MAX_NUMBER_OF_CHARS_IN_INTEGER 10

MatchManager *MatchManager::_matchManager = nullptr;

MatchManager *MatchManager::getInstance() {
    if (_matchManager == nullptr) {
        _matchManager = new MatchManager();
    }
    return _matchManager;
}

vector<string> MatchManager::getMazeNames(const vector<Maze *> &mazes) {
    vector<string> mazeNames;
    for (Maze *maze: mazes) {
        mazeNames.push_back(maze->_name);
    }
    return mazeNames;
}

vector<string> MatchManager::getAlgorithmNames(const vector<pair<string, string>> &soFiles) {
    vector<string> algoNames;
    for (auto &algo : soFiles) {
        algoNames.push_back(algo.second);
    }
    return algoNames;
}

void MatchManager::startGame(const vector<Maze *> &mazes, const vector<pair<string, string>> &soFiles,
                             const string &outputDir) {
    Results res(getMazeNames(mazes), getAlgorithmNames(soFiles)); //todo need to put real vectors!!!
    for (auto &algo : soFiles) {
        void *dynLibHandle = dlopen(algo.first.c_str(), RTLD_NOW);
        for (Maze *maze :mazes) {
            unique_ptr<GameManager> gameManager = make_unique<GameManager>(*maze, outputDir, algo.second, _algorithms[_algorithms.size() - 1]());
            int numOfSteps = gameManager->startGame();
            res.add(algo.second, maze->_name, numOfSteps);
        }
        getInstance()->_dlPlayerAlgorithms.push_back(dynLibHandle);
    }
    _algorithms.clear();
    closeDll();
    res.print();
}

void MatchManager::closeDll() {
    for (auto alg :getInstance()->_dlPlayerAlgorithms) {
        dlclose(alg);
    }
}


/*
 * RESULTS
 */

MatchManager::Results::Results(const vector<string> &mazeNames, const vector<string> &algoNames) {
    _mazeNames = mazeNames;
    _algoNames = algoNames;
    _stepsTaken = new int *[_algoNames.size()];
    for (unsigned i = 0; i < _algoNames.size(); ++i)
        _stepsTaken[i] = new int[_mazeNames.size()];
}

MatchManager::Results::~Results() {
    for (unsigned i = 0; i < _algoNames.size(); ++i) {
        delete[] _stepsTaken[i];
    }
    delete[] _stepsTaken;
}


int MatchManager::Results::getMazeNameIndex(const string &mazeName) {
    return distance(_mazeNames.begin(), find(_mazeNames.begin(), _mazeNames.end(), mazeName));
}

int MatchManager::Results::getAlgoNameIndex(const string &algoName) {
    return distance(_algoNames.begin(), find(_algoNames.begin(), _algoNames.end(), algoName));
}

int MatchManager::Results::getLongestStringSize(const vector<string> &vec) {
    unsigned max = 0;
    for (auto const &str: vec) {
        if (str.size() > max) {
            max = str.size();
        }
    }
    return max;
}

int MatchManager::Results::getCellWidth() {
    return max(MAX_NUMBER_OF_CHARS_IN_INTEGER, max(getLongestStringSize(_algoNames), getLongestStringSize(_mazeNames)));
}

void MatchManager::Results::add(string algoName, string mazeName, int numOfSteps) {
    _stepsTaken[getAlgoNameIndex(algoName)][getMazeNameIndex(mazeName)] = numOfSteps;
}

void MatchManager::Results::print() {
    int numOfSteps;
    int cellWidth = getCellWidth();
    int numOfColSeparators = _mazeNames.size() + 2;
    unsigned int width = (_mazeNames.size() + 1) * cellWidth + (numOfColSeparators);
    cout << string(width, '-') << endl;
    //print maze names header
    cout << "|" << setw(cellWidth) << " ";
    for (auto const &mazeName: _mazeNames) {
        cout << "|" << left << setw(cellWidth) << mazeName;
    }
    cout << "|" << endl;
    cout << string(width, '-') << endl;
    //print results for each algorithm
    for (auto const &algoName: _algoNames) {
        cout << "|" << left << setw(cellWidth) << algoName;
        for (auto const &mazeName: _mazeNames) {
            numOfSteps = _stepsTaken[getAlgoNameIndex(algoName)][getMazeNameIndex(mazeName)];
            cout << "|" << setw(cellWidth) << numOfSteps;
        }
        cout << "|" << endl;
        cout << string(width, '-') << endl;
    }
}

