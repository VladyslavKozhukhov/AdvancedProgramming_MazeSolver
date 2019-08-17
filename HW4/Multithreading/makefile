COMP = g++-8.3.0
OBJS =  main.o Algorithm.o AStarAlgorithm.o RandomMovementAlgorithm.o GameData.o GameManager.o Player.o

EXEC = 9-puzzle
CPP_COMP_FLAG = -std=c++17 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
main.o: main.cpp GameManager.h Player.h Match.h RandomMovementAlgorithm.h AStarAlgorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Algorithm.o: Algorithm.cpp Algorithm.h GameData.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AStarAlgorithm.o: AStarAlgorithm.cpp AStarAlgorithm.h Algorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RandomMovementAlgorithm.o: RandomMovementAlgorithm.cpp RandomMovementAlgorithm.h Algorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameData.o: GameData.cpp GameData.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.cpp GameManager.h GameData.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.cpp Player.h Algorithm.h GameData.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)

	