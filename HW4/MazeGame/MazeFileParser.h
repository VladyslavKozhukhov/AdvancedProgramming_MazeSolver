#ifndef MAZESOLVER_PARSER_H
#define MAZESOLVER_PARSER_H

#include <memory>
#include "Maze.h"
#include "ParserErrorHandler.h"

using namespace std;
typedef pair<char,pair<int,int> > badChar;
typedef vector<badChar> badCharVector;

class MazeFileParser {
public:
    MazeFileParser(ifstream& inputFileStream,shared_ptr<Maze> maze);
    void parse();
private:
    ifstream& _inputFileStream;
    shared_ptr<Maze> _maze;
    int _lineNumber = 0;
    int _numOfPlayers = 0;
    int _numOfExists = 0;
    void handlePartialHeader() const;
    void parseHeader();
    void parseMap(badCharVector &badChars);
    void handleMazeErrors(const badCharVector &vecOfBadChars);
    bool legalCharInMaze(char c);
    int getValueFromExpression(const string& line);
    void ltrim(string &s);
    void rtrim(string &s);
    void trim(string &s);
};

#endif //MAZESOLVER_PARSER_H
