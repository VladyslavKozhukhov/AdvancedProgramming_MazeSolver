#include <unistd.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include "FileHandler.h"

const char LINE_SEPERATOR =
#ifdef _WIN32
        '\\';
#else
'/';
#endif

#define MAZE_EXTENSION ".maze"
#define MAZE_EXTENSION_LEN 5
#define ALGO_EXTENSION ".so"
#define ALGO_EXTENSION_LEN 3


//string FileHandler::getFilePath(const string &fullPathToFile) {
//    return fullPathToFile.substr(0, fullPathToFile.find_last_of(LINE_SEPERATOR));
//}

//void FileHandler::printOutputFileError(string outputFileName) {
//    cout << "Command line argument for output file: " << outputFileName <<
//         " points to a bad path or to a file that already exists" << endl;
//}

//bool FileHandler::isPath(const string &fullPathToFile) {
//    return fullPathToFile.find(LINE_SEPERATOR) != string::npos;
//}

//bool FileHandler::fileExists(const string &fullPathToFile) {
//    return access(fullPathToFile.c_str(), F_OK) != -1;
//}


//bool FileHandler::isPossibleCreatingNewFile(const string &fullPathToFile) {
//    if (fileExists(fullPathToFile) || !pathExists(fullPathToFile)) {
//        printOutputFileError(fullPathToFile);
//        return false;
//    }
//    return true;
//}

/**
 * @param path
 * @return pair which contains full path to file and file name
 */
vector<pair<string, string>> FileHandler::getAllFilesInPath(const string &path) {
    vector<pair<string, string>> files;
    DIR *dirp;
    if (path.empty()) {
        dirp = opendir("./");
    } else {
        dirp = opendir(path.c_str());
    }
    struct dirent *dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_name[0] != '.') {
            files.emplace_back(make_pair(createFullPathToFile(path, dp->d_name), dp->d_name));
        }
    }
    closedir(dirp);
    return files;
}

vector<pair<string, string>> FileHandler::getSoFiles() {
    vector<pair<string, string>> files = getAllFilesInPath(_algoDir);
    auto condition = [](const pair<string, string> &file) {
        return file.first.substr(file.first.size() - ALGO_EXTENSION_LEN) != ALGO_EXTENSION;
    };
    files.erase(remove_if(files.begin(), files.end(), condition), files.end());
    for (auto &file: files) { //remove so extension from file names
        file.second.erase(file.second.size() - 3);
    }
    return files;
}

vector<pair<string, string>> FileHandler::getMazeFiles() {
    vector<pair<string, string>> files = getAllFilesInPath(_mazeDir);
    auto condition = [](const pair<string, string> &file) {
        return file.first.substr(file.first.size() - MAZE_EXTENSION_LEN) != MAZE_EXTENSION;
    };
    files.erase(remove_if(files.begin(), files.end(), condition), files.end());
    return files;
}

bool FileHandler::pathExists(const string &fullPathToFile) {
    return access(fullPathToFile.c_str(), F_OK) == 0;
}

string FileHandler::createFullPathToFile(const string &basePath, const string &fileName) {
    return basePath + LINE_SEPERATOR + fileName;
}

bool FileHandler::isFileOpen(const ifstream &file, const string &fullPathToFile) {
    if (!file.is_open()) {
        cout << "Command line argument for maze: " << fullPathToFile <<
             " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
        return false;
    }
    return true;
}

FileHandler::FileHandler(int argc, char **argv) {
    const string maze_path_flag = "-maze_path";
    const string output_path_flag = "-output";
    const string algorithm_path_flag = "-algorithm_path";
    _mazeDir = ".";
    _algoDir = ".";
    for (int i = 1; i < argc - 1; i++) {
        if (argv[i] == maze_path_flag && pathExists(argv[i + 1])) {
            _mazeDir = argv[++i];
        } else if (argv[i] == algorithm_path_flag && pathExists(argv[i + 1])) {
            _algoDir = argv[++i];
        } else if (argv[i] == output_path_flag && pathExists(argv[i + 1])) {
            _outputDir = argv[++i];
        }
    }
}