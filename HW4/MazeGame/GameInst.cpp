//
// Created by vladko on 6/12/19.
//

#include "GameInst.h"
#define MAX_NUM_OF_STEPS_TO_TRY 100000
#define MIN_NUM_OF_TRIES 100
string GameInst::turn = "1";
GameInst::GameInst(Maze &maze, const string &outputDir,const string &algoName) :
        _maze(maze),
        _outputDir(outputDir),
        _algoName(algoName)
{
//    _algoNum= "1";
    _bookMarkVec.insert(std::make_pair(0, 0));
    _currentPosition = _maze._playerStartLocation;
    winGameTotal = false;
     winGame = GameInst::Move::CONT;
     numOfTries =1;// std::max(MAX_NUM_OF_STEPS_TO_TRY / _maze._maxSteps, MIN_NUM_OF_TRIES);
     numberOfStepsTaken = _maze._maxSteps ;
     movements = new stack<char>;
     steps = 0;
    _path = stack< Move>();

     index = 0;

}
bool GameInst::getTotalWin(){
    if (!_outputDir.empty() && endGame) {
        printPath(movements, winGameTotal);
//        _path = stack< Move>();
    }
    return endGame;
}

pair<int, int> GameInst::getNewPlayerCordinates( Move move) {
    pair<int, int> newPlayerPosition = _currentPosition;
    switch (move) {
        case  Move::UP:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first - 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case  Move::DOWN:
            newPlayerPosition.first =
                    (_maze._numOfRows + (newPlayerPosition.first + 1) % _maze._numOfRows) % _maze._numOfRows;
            break;
        case  Move::RIGHT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second + 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        case  Move::LEFT:
            newPlayerPosition.second =
                    (_maze._numOfCols + (newPlayerPosition.second - 1) % _maze._numOfCols) % _maze._numOfCols;
            break;
        default:
            break;
    }

    return newPlayerPosition;
}

int GameInst::getScore(){
//    std::cout<<getTotalWin()<<endl;
    return steps;

}
GameInst::Move GameInst::validateMove(pair<int, int> locToCheck,  Move playerMove, stack<char> *movements,
                               unsigned *numberOfStepsTaken) {
const char END ='$';
const  char WALL = '#';

    matrix *maze = _maze.getMap();
    switch ((*maze)[locToCheck.first][locToCheck.second]) {
        case WALL:
            return Move::HITWALL;
        case END:
            _path.push(playerMove);
            if (_path.size() < *numberOfStepsTaken) {
                *numberOfStepsTaken = _path.size();
                copyPath(movements);
            }
            _path = stack< Move>();
            return Move::ENDGAME;
        default :
            _currentPosition = locToCheck;
            _path.push(playerMove);
            return Move::CONT;

    }
}
void GameInst::copyPath(stack<char>* movements){
    while (!movements->empty())
        movements->pop();
    while (!_path.empty()) {
        movements->push(convertMovToChar(_path.top()));
        _path.pop();
    }
}
void GameInst::printPath(stack<char>* movements,bool success){
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
string GameInst::getOutputFileFullPath() {
    string mazeName(_maze._name);
    replace(mazeName.begin(), mazeName.end(), ' ', '_');
    string tmpAlgoNum = GameInst::turn;
    GameInst::turn = GameInst::turn=="1"?"2":"1";
    string retVal =  _outputDir + "/" + mazeName + "_" + tmpAlgoNum + ".output";
//    cout<<retVal<<endl;
    return retVal;
}
char GameInst::convertMovToChar(GameInst::Move move) {
    switch (move) {
        case GameInst::Move::DOWN:
            return 'D';
        case GameInst::Move::UP:
            return 'U';
        case GameInst::Move::LEFT:
            return 'L';
        case GameInst::Move::RIGHT:
            return 'R';
        default:
            return '*';
    }
}
int GameInst::validateHitWithBookMark(pair<int, int> locToCheck) {
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
GameInst::Move  GameInst::procc(Move playerMove) {
    if (numOfTries == 0) {
        if (!winGameTotal) {
            steps =movements->size();
            copyPath(movements);
        }
        else{
            steps =movements->size();
            copyPath(movements);


        }
//        if (!_outputDir.empty()) {
//            printPath(movements, winGameTotal);
//        }
        endGame =true;

        return Move::ENDGAME;
    }
    else if (numOfTries > 0 && steps<_maze._maxSteps) {

        pair<int, int> locToCheck;
        if (playerMove != Move::BOOKMARK) {
            locToCheck = getNewPlayerCordinates(playerMove);
            index = validateHitWithBookMark(locToCheck);
            if (index != -1) {
                _path.push(playerMove);
                steps++;
                return Move::HITBOOKMARK;
            } else if (index == -1 || _currentPosition == _maze._playerStartLocation) {
                winGame = validateMove(locToCheck, playerMove, movements, &numberOfStepsTaken);
                if (winGame ==  Move::ENDGAME) {
                    winGameTotal = true;
//                    std::cout<<"WIN "<<steps<<std::endl;
//                    std::cout<<steps<<endl;
//                    steps = _maze._maxSteps;
                    endGame =true;
                    numOfTries--;

                }
                steps++;
                return winGame;

            }
        } else {
            steps++;


            _bookMarkVec.insert(_currentPosition);
            return Move::CONT;

        }

    }
    numOfTries--;
    steps = -1;
    endGame =true;
    copyPath(movements);
    return Move::ENDGAME;
}