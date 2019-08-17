#include "GameManager.h"

#define WALL  '#'
#define SPACE ' '
#define PLAYER '@'
#define END '$'

#define MAX_NUM_OF_STEPS_TO_TRY 100000
#define MIN_NUM_OF_TRIES 100

GameManager::GameManager(Maze &maze, const string &outputDir,const string &algoName, unique_ptr<AbstractAlgorithm> player) :
        _maze(maze),
        _outputDir(outputDir),
        _algoName(algoName)
{
    _player = std::move(player);
    _bookMarkVec.insert(std::make_pair(0, 0));
}


pair<int, int> GameManager::getNewPlayerCordinates(AbstractAlgorithm::Move move) {
    pair<int, int> newPlayerPosition = _currentPosition;
    switch (move) {
        case AbstractAlgorithm::Move::UP:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first - 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case AbstractAlgorithm::Move::DOWN:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first + 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case AbstractAlgorithm::Move::RIGHT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second + 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        case AbstractAlgorithm::Move::LEFT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second - 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        default:
            break;
    }

    return newPlayerPosition;
}

bool GameManager::validateMove(pair<int, int> locToCheck, AbstractAlgorithm::Move playerMove, stack<char> *movements,
                               unsigned *numberOfStepsTaken) {
    matrix *maze = _maze.getMap();
    switch ((*maze)[locToCheck.first][locToCheck.second]) {
        case WALL:
            _player->hitWall();
            break;
        case END:
            _path.push(playerMove);
            if (_path.size() < *numberOfStepsTaken) {
                *numberOfStepsTaken = _path.size();
                copyPath(movements);
            }
            _path = stack<AbstractAlgorithm::Move>();
            return true;
        default :
            _currentPosition = locToCheck;
            _path.push(playerMove);
            break;
    }
    return false;
}

int GameManager::validateHitWithBookMark(pair<int, int> locToCheck) {
    int index = -1;
    int counter = 0;
    for (auto it = _bookMarkVec.begin(); it != _bookMarkVec.end(); it++) {
        if (_bookMarkVec.find(locToCheck) == it) {
            index = counter;
            continue;
        }
        counter++;

    }
    return index;
}

int GameManager::startGame() {
    bool winGameTotal = false;
    bool winGame = false;
    int numOfTries = std::max(MAX_NUM_OF_STEPS_TO_TRY / _maze._maxSteps, MIN_NUM_OF_TRIES);
    unsigned numberOfStepsTaken = _maze._maxSteps ;
    stack<char> *movements = new stack<char>;
    int steps;
    int index;
    while (numOfTries > 0) {
        _currentPosition = _maze._playerStartLocation;
        pair<int, int> locToCheck;
        for (int i = 0; i < _maze._maxSteps; i++) {
            //_maze.printMaze(_currentPosition.first,_currentPosition.second,_bookMarkVec);
            AbstractAlgorithm::Move playerMove = _player->move();
            if (playerMove != AbstractAlgorithm::Move::BOOKMARK) {
                locToCheck = getNewPlayerCordinates(playerMove);
                index = validateHitWithBookMark(locToCheck);
                if (index != -1) {
                    _path.push(playerMove);
                    _player->hitBookmark(index);
                } else if (index == -1 || _currentPosition == _maze._playerStartLocation) {
                    winGame = validateMove(locToCheck, playerMove, movements, &numberOfStepsTaken);
                    if (winGame) {
                        winGameTotal = true;

                        i = _maze._maxSteps;
                    }
                }
            } else {
                _bookMarkVec.insert(_currentPosition);
            }
        }
        numOfTries--;
        if (numOfTries == 0) {
            if (!winGameTotal) {
                steps =movements->size();
                copyPath(movements);
            }
            else{
                steps =movements->size();

            }
            if (!_outputDir.empty()) {
                printPath(movements, winGameTotal);
            }
        }
        _path = stack<AbstractAlgorithm::Move>();
    }
    delete movements;

    if (winGameTotal)
        return steps;
    return -1;
}

void GameManager::copyPath(stack<char> *movements) {
    while (!movements->empty())
        movements->pop();
    while (!_path.empty()) {
        movements->push(convertMovToChar(_path.top()));
        _path.pop();
    }
}

char GameManager::convertMovToChar(AbstractAlgorithm::Move move) {
    switch (move) {
        case AbstractAlgorithm::Move::DOWN:
            return 'D';
        case AbstractAlgorithm::Move::UP:
            return 'U';
        case AbstractAlgorithm::Move::LEFT:
            return 'L';
        case AbstractAlgorithm::Move::RIGHT:
            return 'R';
        default:
            return '*';
    }
}

string GameManager::getOutputFileFullPath() {
    string mazeName(_maze._name);
    replace(mazeName.begin(), mazeName.end(), ' ', '_');
    return _outputDir + "/" + mazeName + "_" + _algoName + ".output";
}

void GameManager::printPath(stack<char> *movements, bool success) {
    ofstream outputFileStream(getOutputFileFullPath());
    while (movements->size() > 0) {
        outputFileStream << movements->top() << endl;
        movements->pop();
    }
    if (success) {
        outputFileStream << "!";
    } else {
        outputFileStream << "X";
    }
    outputFileStream.close();
}
