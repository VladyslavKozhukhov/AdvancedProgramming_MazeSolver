#include "GameManager.h"

#define WALL  '#'
#define SPACE ' '
#define PLAYER '@'
#define END '$'

#define MAX_NUM_OF_STEPS_TO_TRY 1000000

GameManager::GameManager(Maze &maze, ofstream &outputFileStream) : _maze(maze), _outputStream(outputFileStream) {}


pair<int, int> GameManager::getNewPlayerCordinates(Movement move) {
    pair<int, int> newPlayerPosition = _currentPosition;
    switch (move) {
        case Movement::UP:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first - 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case Movement::DOWN:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first + 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case Movement::RIGHT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second + 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        case Movement::LEFT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second - 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        case Movement::UNDEF:
        case Movement::BOOKMARK:
            break;

    }
    return newPlayerPosition;
}

void GameManager::startGame() {
    bool winGame = false;
    int numOfTries = MAX_NUM_OF_STEPS_TO_TRY / _maze._maxSteps;
    unsigned int minPath = 0;
    stack<char> movements;
    matrix *maze = _maze.getMap();
    while (numOfTries > 0) {
        _currentPosition = _maze._playerStartLocation;
        Player *player = new Player();
        pair<int, int> bookMark = player->getBookMark();
        pair<int, int> locToCheck;
        for (int i = 0; i < _maze._maxSteps; i++) {
            Movement playerMove = player->move();
            if (playerMove != Movement::BOOKMARK) {
                locToCheck = getNewPlayerCordinates(playerMove);
                if (locToCheck == bookMark)
                    player->hitBookmark();
                switch ((*maze)[locToCheck.first][locToCheck.second]) {
                    case WALL:
                        player->hitWall();
                        break;
                    case END:
                        winGame = true;
                        if (minPath != 0) {
                            if (player->getPath()->size() < minPath) {
                                minPath = player->getPath()->size();
                                copyPath(player->getPath(), &movements);
                            }
                        } else {
                            minPath = player->getPath()->size();
                            copyPath(player->getPath(), &movements);
                        }
                        i = _maze._maxSteps;
                        break;
                    case SPACE:
                        _currentPosition = locToCheck;
                    case PLAYER:
                        _currentPosition = locToCheck;
                        break;
                }
            } else {
                bookMark = _currentPosition;
            }
        }
        numOfTries--;
        if (numOfTries == 0) {
            if (!winGame) {
                copyPath(player->getPath(), &movements);
            }
            printPath(&movements, winGame);
        }
        delete player;
    }
}

void GameManager::copyPath(stack<Cell> *path, stack<char> *movements) {
    while (!movements->empty())
        movements->pop();
    while (!path->empty()) {
        movements->push((char) path->top().getLastTry());
        path->pop();
    }
}

void GameManager::printPath(stack<char> *movements, bool success) {
    while(movements->size()>1){
        _outputStream << movements->top() << endl;
        movements->pop();
    }
    if (success) {
        _outputStream << "!";
    } else {
        _outputStream << "X";
    }
}