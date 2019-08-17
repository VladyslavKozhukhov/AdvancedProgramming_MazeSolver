//
// Created by vladko on 7/1/19.
//

#ifndef HW4_RESULTS_H
#define HW4_RESULTS_H

#include <vector>
#include <iostream>
#include <functional>
#include <iostream>
#include <atomic>
#include <dlfcn.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>

#define MAX_NUMBER_OF_CHARS_IN_INTEGER 10
using namespace std;
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


#endif //HW4_RESULTS_H
