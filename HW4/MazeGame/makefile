COMP = g++-8.3.0


OBJS = FileHandler.o GameManager.o  MazeFileParser.o ParserErrorHandler.o FirstSmartAlgorithm.o GameData.o GameInst.o Match.o

EXECOBJS= $(OBJS) main.o   Maze.o Player.o  SecondSmartAlgorithm.o 

EXEC = mazeGame

CPP_COMP_FLAG = -std=c++17 -g -Wall  -Wextra \
 -pedantic-errors -DNDEBUG -Werror

$(EXEC): $(EXECOBJS)
	$(COMP) -o $(EXEC)  $(EXECOBJS) 
main.o: main.cpp Maze.h FileHandler.h  GameData.h GameManager.h Player.h FirstSmartAlgorithm.h SecondSmartAlgorithm.h MazeFileParser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FirstSmartAlgorithm.o: FirstSmartAlgorithm.cpp FirstSmartAlgorithm.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
SecondSmartAlgorithm.o: SecondSmartAlgorithm.cpp SecondSmartAlgorithm.h AbstractAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileHandler.o: FileHandler.cpp FileHandler.h
	$(COMP)  $(CPP_COMP_FLAG) -c $*.cpp
GameData.o: GameData.cpp GameData.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
GameInst.o: GameInst.cpp GameInst.h Maze.h GameData.h 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameInst.h GameData.h
	$(COMP)  $(CPP_COMP_FLAG) -c $*.cpp

Match.o: Match.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.cpp Player.h GameData.h SecondSmartAlgorithm.h FirstSmartAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MazeFileParser.o: MazeFileParser.cpp MazeFileParser.h ParserErrorHandler.h Maze.h
	$(COMP)  $(CPP_COMP_FLAG) -c $*.cpp
ParserErrorHandler.o: ParserErrorHandler.cpp ParserErrorHandler.h
	$(COMP)  $(CPP_COMP_FLAG) -c $*.cpp
Maze.o:	Maze.cpp Maze.h
	$(COMP)  $(CPP_COMP_FLAG) -c $*.cpp


clean:
	rm -f *.o $(EXEC)
