#ifndef MAZESOLVER_ERRORHANDLER_H
#define MAZESOLVER_ERRORHANDLER_H

#include <string>
#include <vector>

using namespace std;

enum ErrorStatus {
    MaxStepsError, //header errors
    Col_Issue,
    Row_Issue,
    Missing_Player, //maze errors
    Missing_End,
    More_Than_One_Player,
    More_Than_One_End,
    Wrong_Character
};

class ParserErrorHandler{
public:
    static void printError(ErrorStatus err, const vector<string> &args = {});
    static bool noErrorsFound();
    static bool isHeaderValid(){ return !_inputFileContainsHeaderErrors; };
    static bool _inputFileContainsHeaderErrors;
    static bool _inputFileContainsMazeErrors;
private:

    static void setHeaderErrorIfNeeded();
    static void setMazeErrorIfNeeded();
};


#endif //MAZESOLVER_ERRORHANDLER_H
