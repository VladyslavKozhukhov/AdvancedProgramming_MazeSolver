COMP = g++#-5.3.0
LIBS = -ldl
default:
	make match

OBJS =   FileHandler.o GameManager.o  MazeFileParser.o ParserErrorHandler.o

EXECOBJS= $(OBJS) main.o MatchManager.o AlgorithmRegistration.o Maze.o

EXEC = match
CPP_COMP_FLAG = -std=c++14 -g -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG
#CPP_COMP_FLAG = -std=c++14 -g  -pedantic-errors -DNDEBUG

$(EXEC): $(EXECOBJS)
	$(COMP) -rdynamic -o $(EXEC)  $(EXECOBJS) $(LIBS)

MatchManager.o:MatchManager.h MatchManager.cpp GameManager.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

main.o: main.cpp Maze.h MatchManager.h ParserErrorHandler.h FileHandler.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileHandler.o: FileHandler.cpp FileHandler.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h MazeFileParser.h AbstractAlgorithm.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
MazeFileParser.o: MazeFileParser.cpp MazeFileParser.h ParserErrorHandler.h Maze.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
ParserErrorHandler.o: ParserErrorHandler.cpp ParserErrorHandler.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
Maze.o:	Maze.cpp Maze.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp

AlgorithmRegistration.o:AlgorithmRegistration.h AlgorithmRegistration.h AbstractAlgorithm.h MatchManager.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp


match: $(EXEC) $(EXECOBJS)


clean:
	rm -f *.so *.o $(EXEC)
