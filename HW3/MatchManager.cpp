#include "MatchManager.h"
#include "MatchManager.h"
#include <algorithm>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <atomic>

#define MAX_NUMBER_OF_CHARS_IN_INTEGER 10

MatchManager *MatchManager::_matchManager = nullptr;

MatchManager *MatchManager::getInstance() {
    if (_matchManager == nullptr) {
        _matchManager = new MatchManager();
    }
    return _matchManager;
}

vector<string> MatchManager::getMazeNames(vector<shared_ptr<Maze>> mazes) {
    vector<string> mazeNames;
    for (auto maze: mazes) {
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

//todo 1) refactor this , change new to smart por

void MatchManager::threadRunGameManager() {

    while (getInstance()->_totalNumOfGamesToRun > 0) {
        getInstance() -> _totalNumOfGamesToRun--;
        unique_ptr<GameManager> gameManager;
        string mazeName = "";
        string algName = "";
        getInstance()->_matchMutex.lock();
        int counter = 0;
        bool choose;
        for (auto &mazeRun: getInstance()->_completedGames) {
            choose = false;
            for (unsigned indexAlgo = 0; indexAlgo < getInstance()->_algoNamesLst.size(); indexAlgo++) {
                if (!mazeRun.second.at(indexAlgo)) {
                    algName = getInstance()->_algoNamesLst.at(indexAlgo);
                    mazeName = (*getInstance()->_mazes.at(counter))._name;
                    gameManager = make_unique<GameManager>(*getInstance()->_mazes.at(counter), getInstance()->_outputDir,
                                                           algName, getInstance()->_registeredAlgorithms[int(indexAlgo)]());
                    mazeRun.second.at(indexAlgo) = true;
                    choose = true;
                    break;
                }
            }
            if (choose)
                break;
            counter++;

        }
        getInstance()->_matchMutex.unlock();

        int numOfSteps = gameManager->startGame();

        getInstance()->_matchMutex.lock();
        getInstance()->_res->add(algName, mazeName, numOfSteps);
        getInstance()->_matchMutex.unlock();

    }
}

void MatchManager::closeAllDynLibs() {
    for (auto alg :getInstance()->_dlPlayerAlgorithms) {
        dlclose(alg);
    }
}

void MatchManager::openAllDynLibs(const vector<pair<string, string>> &soFiles) {
    for (auto &algo : soFiles) {
        void *dynLibHandle = dlopen(algo.first.c_str(), RTLD_NOW);
        _dlPlayerAlgorithms.push_back(dynLibHandle);
    }
}


void
MatchManager::startGame(vector<shared_ptr<Maze>> mazes, int numOfThreads, const vector<pair<string, string>> &soFiles,
                        const string &outputDir) {
    vector<string> mazeNames = getMazeNames(mazes);
    _algoNamesLst = getAlgorithmNames(soFiles);
    _res = make_unique<Results>(mazeNames,_algoNamesLst);
    _mazes = mazes;
    _outputDir = outputDir;
    openAllDynLibs(soFiles);
    createCompletedGameMatrix(soFiles.size(), mazeNames);
    _totalNumOfGamesToRun = mazes.size() * soFiles.size();
    vector<thread> listOfThreads;
    for (int i = 0; i < numOfThreads; i++) {
        listOfThreads.push_back(thread(threadRunGameManager));
    }
    for (int i = 0; i < (int) listOfThreads.size(); i++) {
        listOfThreads[i].join();
    }
    _registeredAlgorithms.clear();
    closeAllDynLibs();
    _res->print();
}

//completed games contains a tuple: {Name of maze, vector of booleans where vec[i]=true -> algorithm i tried solving maze}
void MatchManager::createCompletedGameMatrix(unsigned numOfAlgorithms, vector<string> &mazeNames) const {
    for (unsigned i = 0; i < getInstance()->_mazes.size(); i++) {
        getInstance()->_completedGames.insert(
                pair<string, vector<bool>>(mazeNames.at(i), vector<bool>(numOfAlgorithms, false)));
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

