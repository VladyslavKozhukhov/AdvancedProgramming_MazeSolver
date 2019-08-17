//========================================
// File: "Match.h"
// You shouldn't change anything
// we may replace it with our "Match.h" 
//========================================
// you should have #pragma once -- or #ifndef guards
#pragma once
// (here it is in a comment as we are in coliru inside a single cpp file)

#include <functional>
#include <vector>
#include <thread>

//-----------------
// Match Manager
//-----------------
template<typename GameManager, typename GameData, typename Player, typename PlayerFactory = std::function<Player(typename GameData::InitData)>>
class Match {
    GameManager game_manager;
    std::vector<GameData> games;
    std::vector<PlayerFactory> players;
    std::vector<std::thread> threads;
public:
    explicit Match(GameManager gm): game_manager{std::move(gm)} {}
    void addGame(GameData gd) {
        games.push_back(std::move(gd));
    }
    void addPlayer(PlayerFactory p) {
        players.push_back(std::move(p));    
    }
    using ReportField = std::pair<typename GameData::Id, std::vector<std::pair<typename Player::Id, int>>>;
    using Report = std::vector<ReportField>;
    Report runMatch() {
        Report report;
        for (auto &game : games) {
            // note: needs C++17, emplace_back returns reference to the newly created item only from C++17
            auto &gameReport = report.emplace_back(game.id(), std::vector<std::pair<typename Player::Id, int>>{});
            for (auto &playerFactory : players) {
                runGame(game,playerFactory,gameReport);
                threads.push_back(std::thread(&Match::runGame ,game, playerFactory, report));
            }
        }
        for(auto& thread : threads){
            thread.join();
        }
        return report;
    }
    void runGame(GameData& game, PlayerFactory& playerFactory, ReportField& gameReport){
        typename GameData::GameInstanceData gameInstance = game.newGameInstance();
        typename GameData::InitData gameInitData = game_manager.getInitData(game, gameInstance);
        Player player = playerFactory(gameInitData);
        while (!game_manager.endGame(game, gameInstance)) {
            typename GameData::Move move = player.move();
            typename GameData::MoveFeedback feedback = game_manager.processMove(game, gameInstance, move);
            player.moveFeedback(feedback);
        }
        gameReport.second.emplace_back(player.id(), game_manager.score(game, gameInstance));
    }
};
//========================================
// End of File: "Match.h"
//========================================
