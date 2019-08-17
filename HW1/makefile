COMP = g++-5.3.0
OBJS =  main.o FileHandler.o GameManager.o  Parser.o ParserErrorHandler.o Player.o Maze.o

EXEC = ex1
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
main.o: main.cpp Maze.h GameManager.h ParserErrorHandler.h FileHandler.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FileHandler.o: FileHandler.cpp FileHandler.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h Parser.h Player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp Parser.h ParserErrorHandler.h Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ParserErrorHandler.o: ParserErrorHandler.cpp ParserErrorHandler.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.cpp Player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Maze.o:	Maze.cpp Maze.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)

	