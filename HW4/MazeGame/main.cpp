#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "FileHandler.h"
#include "Match.h"
#include "GameData.h"
#include "GameManager.h"
#include "Player.h"
#include <functional>
#include "FirstSmartAlgorithm.h"
#include "SecondSmartAlgorithm.h"
#include "MazeFileParser.h"
#include <functional>
#include "AbstractAlgorithm.h"

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

//    MatchManager::getInstance()->startGame(mazes,fileHandler.getNumOfThreads(),fileHandler.getSoFiles(),fileHandler.getOutputDir());

    using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
//    AbstractAlgorithm * algo1 = new FirstSmartAlgorithm();
//    AbstractAlgorithm * algo2 = new SecondSmartAlgorithm();
//    unique_ptr<AbstractAlgorithm> algo1 = make_unique<FirstSmartAlgorithm>();
//    unique_ptr<AbstractAlgorithm> algo2 = make_unique<SecondSmartAlgorithm>();
    auto algo1 = FirstSmartAlgorithm();
    auto algo2 = SecondSmartAlgorithm();
    MyMatch match{g};
//    match.addPlayer(
//            [algo1](GameData::InitData init){
//                return Player{init,algo1};// []{ return FirstSmartAlgorithm();}};
//            }
//    );
    match.addPlayer(
            [&algo1](GameData::InitData init){
                return Player{init,algo1};// []{ return FirstSmartAlgorithm();}};
            }
    );
    match.addPlayer(
            [&algo2](GameData::InitData init){
                return Player{init, algo2};//[]{ return SecondSmartAlgorithm();}};
            }
    );
    for(auto maze : mazes){
        match.addGame(GameData(maze,fileHandler.getOutputDir(),maze->_name));
    }
    MyMatch::Report report = match.runMatch();
    // T

    for (const auto &val : report) {
        cout << "GAME: " << val.first << endl;
        for (const auto &playerRes : val.second) {

            cout << "Algorithm "<< playerRes.first << " - SCORE: " << ((int)playerRes.second==-1?-1:((int)playerRes.second - 1)) << endl;
        }
    }
//    delete algo1;
//    delete algo2;
    return 0;
}
