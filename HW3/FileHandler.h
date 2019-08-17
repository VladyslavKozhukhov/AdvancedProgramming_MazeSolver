#ifndef MAZESOLVER_FILEHANDLER_H
#define MAZESOLVER_FILEHANDLER_H

#include <string>
#include <vector>
#include <tuple>
#include <ctype.h>

using namespace std;

class FileHandler{
    string _mazeDir;
    string _algoDir;
    string _outputDir;
    int _numOfThreads;
    vector<pair<string,string>> getAllFilesInPath(const string &path);
    bool pathExists(const string &fullPathToFile);
    string createFullPathToFile(const string& basePath, const string& fileName);
public:
    bool isNumber(string number);
    int getNumOfThreads(){return _numOfThreads;}
    FileHandler(int argc,char** argv);
    vector<pair<string,string>> getSoFiles();
    vector<pair<string,string>> getMazeFiles();
    string getOutputDir() { return _outputDir; }
    bool isFileOpen(const ifstream& file, const string& fullPathToFile);
};

#endif //MAZESOLVER_FILEHANDLER_H
