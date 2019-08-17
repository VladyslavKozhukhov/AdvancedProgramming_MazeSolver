//
// Created by vladko on 6/11/19.
//

#ifndef MAZESOLVERMANNAGER_MATCH_H
#define MAZESOLVERMANNAGER_MATCH_H
#include <functional>
#include <vector>

//-----------------
// Match Manager
//-----------------
template<typename GameManager, typename GameData, typename Player, typename PlayerFactory = std::function<Player(typename GameData::InitData)>>
class Match {
    GameManager game_manager;
    std::vector<GameData> games;
    std::vector<PlayerFactory> players;
public:
    explicit Match(GameManager gm): game_manager{std::move(gm)} {}
    void addGame(GameData gd) {
        games.push_back(std::move(gd));
    }
    void addPlayer(PlayerFactory p) {
        players.push_back(std::move(p));
    }
    using Report = std::vector<std::pair<typename GameData::Id, std::vector<std::pair<typename Player::Id, int>>>>;
    Report runMatch() {
        Report report;
        for(auto& game : games) {
            // note: needs C++17, emplace_back returns reference to the newly created item only from C++17
            auto& gameReport = report.emplace_back(game.id(), std::vector<std::pair<typename Player::Id, int>>{});
            for(auto& playerFactory : players) {
                // gameInstance is per player
                typename GameData::GameInstanceData gameInstance = game.newGameInstance();
                typename GameData::InitData gameInitData = game_manager.getInitData(game, gameInstance);
                Player player = playerFactory(gameInitData);
                while(!game_manager.endGame(game, gameInstance)) {
                    typename GameData::Move move = player.move();
                    typename GameData::MoveFeedback feedback = game_manager.processMove(game, gameInstance, move);
                    player.moveFeedback(feedback);
                }
                gameReport.second.emplace_back(player.id(), game_manager.score(game, gameInstance));
            }
        }
        return report;
    }
};
#endif //MAZESOLVERMANNAGER_MATCH_H
