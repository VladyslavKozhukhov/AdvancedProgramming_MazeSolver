#include <unistd.h>
#include <iostream>
#include <fstream>
#include "FileHandler.h"

#define UNIX_LINE_SEPERATOR '/'

string FileHandler::getFilePath(const string &fullPathToFile) {
    return fullPathToFile.substr(0, fullPathToFile.find_last_of(UNIX_LINE_SEPERATOR));
}

void FileHandler::printOutputFileError(string outputFileName) {
    cout << "Command line argument for output file: " << outputFileName <<
         " points to a bad path or to a file that already exists" << endl;
}

bool FileHandler::isPath(const string &fullPathToFile) {
    return fullPathToFile.find(UNIX_LINE_SEPERATOR) != string::npos;
}

bool FileHandler::fileExists(const string &fullPathToFile) {
    return access(fullPathToFile.c_str(), F_OK) != -1;
}

bool FileHandler::pathExists(const string &fullPathToFile) {
    if(isPath(fullPathToFile)){
        if(access(getFilePath(fullPathToFile).c_str(), F_OK) == -1){
            return false;
        }
    }
    return true;
}

bool FileHandler::isPossibleCreatingNewFile(const string &fullPathToFile) {
    if (fileExists(fullPathToFile) || !pathExists(fullPathToFile)) {
        printOutputFileError(fullPathToFile);
        return false;
    }
    return true;
}

bool FileHandler::isFileOpen(const ifstream &file, const string &fullPathToFile) {
    if (!file.is_open()) {
        cout << "Command line argument for maze: " << fullPathToFile <<
             " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
        return false;
    }
    return true;
}
