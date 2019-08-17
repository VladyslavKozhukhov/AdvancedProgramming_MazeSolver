#include "Parser.h"
#include "ParserErrorHandler.h"
#include <regex>
#include <fstream>

#define WALL '#'
#define SPACE ' '
#define PLAYER '@'
#define END '$'


bool Parser::legalCharInMaze(char c){
    return c==END || c==PLAYER || c==WALL || c==SPACE || c=='\r';
}

Parser::Parser(ifstream& inputFileStream,Maze* maze): _inputFileStream(inputFileStream),_maze(maze) {}

void Parser::handlePartialHeader() const {
    switch (_lineNumber){
        case 0:
        case 1:
            ParserErrorHandler::printError(MaxStepsError,vector<string>{""});
        case 2:
            ParserErrorHandler::printError(Row_Issue,vector<string>{""});
        case 3:
            ParserErrorHandler::printError(Col_Issue,vector<string>{""});
    }
}

int Parser::getValueFromExpression(const string& line){
    const regex number_regex("\\s*(\\d+)\\s*");
    smatch match;
    if(regex_search(line, match, number_regex)){
        return std::stoi(match[1]);
    }
    return 0;
}

void Parser::parseHeader(){
    string line;
    const regex max_steps_regex("\\s*MaxSteps+\\s*=\\s*\\d+\\s*");
    const regex rows_regex("\\s*Rows+\\s*=\\s*\\d+\\s*");
    const regex cols_regex("\\s*Cols+\\s*=\\s*\\d+\\s*");
    while ( _lineNumber < 4 && getline(_inputFileStream,line)) { //first check line num so line will not be read if not needed
        switch(_lineNumber){
            case 1:
                if(regex_match(line,max_steps_regex)){
                    _maze->_maxSteps=getValueFromExpression(line);
                }else{
                    ParserErrorHandler::printError(MaxStepsError,vector<string>{line});
                }
                break;
            case 2:
                if(regex_match(line,rows_regex)){
                    _maze->_numOfRows = getValueFromExpression(line);
                }else{
                    ParserErrorHandler::printError(Row_Issue,vector<string>{line});
                }
                break;
            case 3:
                if(regex_match(line,cols_regex)){
                    _maze->_numOfCols = getValueFromExpression(line);
                }else{
                    ParserErrorHandler::printError(Col_Issue,vector<string>{line});
                }
                break;
        }
        _lineNumber++;
    }
}

void Parser::handleMazeErrors(const badCharVector &vecOfBadChars) {
    if (_numOfPlayers == 0) {
        ParserErrorHandler::printError(ErrorStatus::Missing_Player);
    }
    if (_numOfExists == 0) {
        ParserErrorHandler::printError(ErrorStatus::Missing_End);
    }
    if (_numOfPlayers > 1) {
        ParserErrorHandler::printError(ErrorStatus::More_Than_One_Player);
    }
    if (_numOfExists > 1) {
        ParserErrorHandler::printError(ErrorStatus::More_Than_One_End);
    }
    vector<string> vc;
    for (auto &it:vecOfBadChars) {
        string chr;
        if(it.first == '\t')
        {
            chr = "TAB";
        } else{
            chr += it.first;
        }
        vc.push_back(chr);
        vc.push_back(to_string(it.second.first));
        vc.push_back(to_string(it.second.second));
        ParserErrorHandler::printError(ErrorStatus::Wrong_Character, vc);
        vc.clear();
    }
}

void Parser::parseMaze(badCharVector& badChars){
    string line;
    int row = 0;
    int col;
    while (row<_maze->_numOfRows && getline(_inputFileStream,line)){
        col = 0;
        for (char &c : line) {
            if(col>=_maze->_numOfCols){
                break;
            }
            if(!legalCharInMaze(c)){
                badChars.push_back(badChar(c, pair<int,int>(row+1,col+1))); //file indexes start at 1 -> +1
            }else{
                if(c==END){
                    _numOfExists++;
                }
                if(c==PLAYER){
                    _maze->set_playerStartLocation(row,col);
                    _numOfPlayers++;
                }
            }
            _maze->getMap()->at(row).at(col) = c;
            col++;
        }
        row++;
    }
}

void Parser::parse(){
    parseHeader();
    if(_inputFileStream.eof()){
        handlePartialHeader();
    }
    if(ParserErrorHandler::isHeaderValid()){
        _maze->initMazeMap();
        badCharVector badChars;
        parseMaze(badChars);
        handleMazeErrors(badChars);
    }
}