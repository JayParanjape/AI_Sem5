CXX = g++ -std=c++11 -O3 
CXXFLAGS = -g

main8x8: main8x8.o heuristics8x8.o pruner8x8.o state8x8.o
	$(CXX) $(CXXFLAGS) -o master8x8 main8x8.o heuristics8x8.o pruner8x8.o state8x8.o

main8x8.o: main8x8.cpp heuristics8x8.h pruner8x8.h state8x8.h
	$(CXX) $(CXXFLAGS) -c main8x8.cpp

pruner8x8.o: pruner8x8.h heuristics8x8.h state8x8.h

heuristics8x8.o: heuristics8x8.h

state8x8.o: state8x8.h


main: main.o heuristics.o pruner.o state.o
	$(CXX) $(CXXFLAGS) -o master_108 main.o heuristics.o pruner.o state.o

main.o: main.cpp heuristics.h pruner.h state.h
	$(CXX) $(CXXFLAGS) -c main.cpp

pruner.o: pruner.h heuristics.h state.h

heuristics.o: heuristics.h

state.o: state.h



clean:
	rm *.o