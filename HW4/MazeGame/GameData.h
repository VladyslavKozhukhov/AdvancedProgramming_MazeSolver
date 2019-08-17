#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <memory>
#include "Maze.h"
#include "GameInst.h"
#include <cassert>

#ifndef MAZESOLVERMANNAGER_GAMEDATA_H
#define MAZESOLVERMANNAGER_GAMEDATA_H
class GameData;
class GameData {
//        enum move { UP, RIGHT, DOWN, LEFT, BOOKMARK,HITWALL,HITBOOKMARK ,ENDGAME,CONT};

public:
    //--------------------------
    // required type traits
    //--------------------------
    using Id = std::string;
    using InitData = int;
    using GameInstanceData = GameInst;
    using Move = GameInst::Move ;
    using MoveFeedback = GameInst::Move;

    //--------------------------
    std::shared_ptr<Maze>  _maze;
    string _outputDir;
    Id _id;

    GameData (std::shared_ptr<Maze> maze,const string &outputDir, Id id):_outputDir(outputDir) ,_id(id){
        _maze = maze;
    }
    Id id() const { return _id; }
    GameInstanceData newGameInstance() { return GameInst(*_maze.get(),_outputDir ,_id); }

    MoveFeedback processMove(GameData::GameInstanceData& gameInstance, GameData::Move move) {
        if (!gameInstance.getAlgoName().empty() && move != GameData::Move::UNUSED) {
            return MoveFeedback{};
        }
        else{
            cout<<"check game Instance"<<endl;
            return MoveFeedback{};

        }
    }

};

#endif //MAZESOLVERMANNAGER_GAMEDATA_H