#include "GameManager.h"
#include "Player.h"
#include "Match.h"
#include "RandomMovementAlgorithm.h"
#include "AStarAlgorithm.h"

using namespace std;

int main() {
    using MyMatch = Match<GameManager, GameData, Player>;
    GameManager g;
    MyMatch match{g};
    auto randomAlg = RandomMovementAlgorithm();
    match.addPlayer([&randomAlg](GameData::InitData init) { return Player(init, "PLAYER_1", randomAlg); });
    auto aStarAlg = AStarAlgorithm();
    match.addPlayer([&aStarAlg](GameData::InitData init) { return Player(init, "PLAYER_2", aStarAlg); });
    array<array<int, 3>, 3> game1 = {{{1, 2, 3}, {0, 4, 6}, {7, 5, 8}}};
    array<array<int, 3>, 3> game2 = {{{8, 1, 2}, {3, 4, 5}, {0, 7, 6}}};
    GameData gd1(game1, "GAME_1", 10);
    GameData gd2(game2, "GAME_2", 1000000);
    match.addGame(gd1);
    match.addGame(gd2);
    MyMatch::Report report = match.runMatch();
    for (const auto &val : report) {
        cout << "GAME: " << val.first << endl;
        for (const auto &playerRes : val.second) {
            cout << playerRes.first << " - SCORE: " << playerRes.second << endl;
        }
    }
}
