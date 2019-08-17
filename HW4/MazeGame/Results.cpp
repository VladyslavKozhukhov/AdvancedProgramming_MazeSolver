#include "Results.h"
Results::Results(const vector<string> &mazeNames, const vector<string> &algoNames) {
    _mazeNames = mazeNames;
    _algoNames = algoNames;
    _stepsTaken = new int *[_algoNames.size()];
    for (unsigned i = 0; i < _algoNames.size(); ++i)
        _stepsTaken[i] = new int[_mazeNames.size()];
}
Results::~Results() {
    for (unsigned i = 0; i < _algoNames.size(); ++i) {
        delete[] _stepsTaken[i];
    }
    delete[] _stepsTaken;
}


int Results::getMazeNameIndex(const string &mazeName) {
    return distance(_mazeNames.begin(), find(_mazeNames.begin(), _mazeNames.end(), mazeName));
}

int Results::getAlgoNameIndex(const string &algoName) {
    return distance(_algoNames.begin(), find(_algoNames.begin(), _algoNames.end(), algoName));
}

int Results::getLongestStringSize(const vector<string> &vec) {
    unsigned max = 0;
    for (auto const &str: vec) {
        if (str.size() > max) {
            max = str.size();
        }
    }
    return max;
}

int Results::getCellWidth() {
    return max(MAX_NUMBER_OF_CHARS_IN_INTEGER, max(getLongestStringSize(_algoNames), getLongestStringSize(_mazeNames)));
}

void Results::add(string algoName, string mazeName, int numOfSteps) {
    _stepsTaken[getAlgoNameIndex(algoName)][getMazeNameIndex(mazeName)] = numOfSteps;
}

void Results::print() {
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
