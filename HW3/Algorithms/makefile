COMP = g++-5.3.0
LIBS = -ldl
default:
	make lib
current_dir = $(shell pwd)

LIBOBJS =  FirstSmartAlgorithm.o SecondSmartAlgorithm.o

CPP_LINK_FLAG = -shared

CPP_COMP_FLAG = -std=c++14 -g -Wall -Wextra -Werror\
 -pedantic-errors -DNDEBUG

#CPP_COMP_FLAG = -std=c++14 -g -pedantic-errors -DNDEBUG

#FirstAlgorithm.o:FirstAlgorithm.h FirstAlgorithm.cpp  $(current_dir)/../AbstractAlgorithm.h $(current_dir)/../AlgorithmRegistration.h
#	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
#_332305747_a.so:FirstAlgorithm.o
#	$(COMP) -shared -Wl,-soname,_332305747_a.so -o _332305747_a.so   FirstAlgorithm.o

FirstSmartAlgorithm.o:FirstSmartAlgorithm.h FirstSmartAlgorithm.cpp  $(current_dir)/../AbstractAlgorithm.h $(current_dir)/../AlgorithmRegistration.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
_332305747_a.so:FirstSmartAlgorithm.o
	$(COMP) -shared -Wl,-soname,_332305747_a.so -o _332305747_a.so   FirstSmartAlgorithm.o


#SecondAlgorithm.o:SecondAlgorithm.h SecondAlgorithm.cpp $(current_dir)/../AlgorithmRegistration.h $(current_dir)/../AbstractAlgorithm.h
	#$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
#_332305747_b.so:SecondAlgorithm.o
#	$(COMP) -shared -Wl,-soname,_332305747_b.so -o _332305747_b.so    SecondAlgorithm.o

SecondSmartAlgorithm.o:SecondSmartAlgorithm.h SecondSmartAlgorithm.cpp $(current_dir)/../AlgorithmRegistration.h $(current_dir)/../AbstractAlgorithm.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
_332305747_b.so:SecondSmartAlgorithm.o
	$(COMP) -shared -Wl,-soname,_332305747_b.so -o _332305747_b.so    SecondSmartAlgorithm.o


lib: $(LIBOBJS) _332305747_a.so _332305747_b.so

clean:
	rm -f *.so $(EXEC)
