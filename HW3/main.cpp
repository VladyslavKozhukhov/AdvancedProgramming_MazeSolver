#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "ParserErrorHandler.h"
#include "FileHandler.h"
#include "Maze.h"
#include "MatchManager.h"

using namespace std;

int main(int argc, char **argv) {
    FileHandler fileHandler(argc,argv);
    vector<pair<string,string>> mazeFiles = fileHandler.getMazeFiles();
    vector<shared_ptr<Maze>> mazes;
    for (auto const &file: mazeFiles) {
        ifstream inputFileStream(file.first);
        if (fileHandler.isFileOpen(inputFileStream, file.first)) {
            shared_ptr<Maze> maze = make_shared<Maze>();
            MazeFileParser parser(inputFileStream, maze);
            parser.parse();
            if (ParserErrorHandler::noErrorsFound()) {
                mazes.push_back(maze);
            }
        }
        inputFileStream.close();
    }
    MatchManager::getInstance()->startGame(mazes,fileHandler.getNumOfThreads(),fileHandler.getSoFiles(),fileHandler.getOutputDir());
    return 0;
}
