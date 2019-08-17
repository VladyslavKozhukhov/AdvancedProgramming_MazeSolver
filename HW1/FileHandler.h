#ifndef MAZESOLVER_FILEHANDLER_H
#define MAZESOLVER_FILEHANDLER_H

#include <string>

using namespace std;


class FileHandler{
    static string getFilePath(const string& fullPathToFile);
    static bool isPath(const string &fullPathToFile);
    static bool fileExists(const string &fullPathToFile);
    static bool pathExists(const string &fullPathToFile);
public:
    static bool isPossibleCreatingNewFile(const string& fullPathToFile);
    static bool isFileOpen(const ifstream& file, const string& fullPathToFile);
    static void printOutputFileError(string outputFileName);
};

#endif //MAZESOLVER_FILEHANDLER_H
