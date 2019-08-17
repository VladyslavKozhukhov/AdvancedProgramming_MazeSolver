#include <iostream>
#include <fstream>
#include "ParserErrorHandler.h"

bool ParserErrorHandler::_inputFileContainsHeaderErrors = false;
bool ParserErrorHandler::_inputFileContainsMazeErrors = false;

void ParserErrorHandler::setHeaderErrorIfNeeded() {
    if (!_inputFileContainsHeaderErrors) {
        _inputFileContainsHeaderErrors = true;
        cout << "Bad maze file header:" << endl;
    }
}

void ParserErrorHandler::setMazeErrorIfNeeded() {
    if (!_inputFileContainsMazeErrors) {
        _inputFileContainsMazeErrors = true;
        cout << "Bad maze in maze file:" << endl;
    }
}

bool ParserErrorHandler::noErrorsFound() {
    return !(_inputFileContainsHeaderErrors || _inputFileContainsMazeErrors);
}

void ParserErrorHandler::printError(ErrorStatus err, const vector<string> &args) {
    switch (err) {
        case MaxStepsError:
            setHeaderErrorIfNeeded();
            cout << "expected in line 2 - MaxSteps = <num>" << endl;
            cout << "got: " << args[0] << endl;
            break;
        case Row_Issue:
            setHeaderErrorIfNeeded();
            cout << "expected in line 3 - Rows = <num>" << endl;
            cout << "got: " << args[0] << endl;
            break;
        case Col_Issue:
            setHeaderErrorIfNeeded();
            cout << "expected in line 4 - Cols = <num>" << endl;
            cout << "got: " << args[0] << endl;
            break;
        case Missing_Player:
            setMazeErrorIfNeeded();
            cout << "Missing @ in maze" << endl;
            break;
        case Missing_End:
            setMazeErrorIfNeeded();
            cout << "Missing $ in maze" << endl;
            break;
        case More_Than_One_Player:
            setMazeErrorIfNeeded();
            cout << "More than one @ in maze" << endl;
            break;
        case More_Than_One_End:
            setMazeErrorIfNeeded();
            cout << "More than one $ in maze" << endl;
            break;
        case Wrong_Character:
            setMazeErrorIfNeeded();
            cout << "Wrong character in maze: " << args[0] <<
                 " in row " << args[1] << ", col " << args[2] << endl;
            break;
    }
}



