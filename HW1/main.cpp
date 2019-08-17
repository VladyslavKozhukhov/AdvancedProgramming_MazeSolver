#include <iostream>
#include "GameManager.h"//delete from here
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "ParserErrorHandler.h"
#include "FileHandler.h"
#include "Maze.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc == 1) {
        cout << "Missing maze file argument in command line" << endl;
    }
    if (argc <= 2) {
        cout << "Missing output file argument in command line" << endl;
    }
    if (argc >= 2) {
        string inputFile(argv[1]);
        string outputFile;
        ifstream inputFileStream(inputFile);
        bool validInput = FileHandler::isFileOpen(inputFileStream, inputFile);
        bool validOutputPath = false;
        if (argc == 3) {
            outputFile = argv[2];
            validOutputPath = FileHandler::isPossibleCreatingNewFile(outputFile);
        }
        if (validInput) {
            Maze *maze = new Maze();
            Parser parser(inputFileStream, maze);
            parser.parse();
            inputFileStream.close();
            if (ParserErrorHandler::noErrorsFound() && validOutputPath) {
                ofstream outputFileStream(outputFile); //create output file only if: path exists,
                if (!outputFileStream.is_open()) {       //file doesn't exist and no parser errors found
                    FileHandler::printOutputFileError(outputFile);
                } else {
                    GameManager manager(*maze, outputFileStream);
                    manager.startGame();//7
                    outputFileStream.close();
                    delete maze->_mazeMap;
                }
            }
            delete maze;
        }
    }
    return 0;
}