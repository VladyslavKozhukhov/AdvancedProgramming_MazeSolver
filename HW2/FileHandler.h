#ifndef MAZESOLVER_FILEHANDLER_H
#define MAZESOLVER_FILEHANDLER_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

class FileHandler{
//    static string getFilePath(const string& fullPathToFile);
//    static bool fileExists(const string &fullPathToFile);
    string _mazeDir;
    string _algoDir;
    string _outputDir;
    vector<pair<string,string>> getAllFilesInPath(const string &path);
    bool pathExists(const string &fullPathToFile);
    string createFullPathToFile(const string& basePath, const string& fileName);
public:
    FileHandler(int argc,char** argv);
    vector<pair<string,string>> getSoFiles();
    vector<pair<string,string>> getMazeFiles();
    string getOutputDir() { return _outputDir; }
    bool isFileOpen(const ifstream& file, const string& fullPathToFile);
};

#endif //MAZESOLVER_FILEHANDLER_H
