CXX = g++ -std=c++11
CXXFLAGS = -Wall -g

main_code: main_code.o loss.o IO.o
	$(CXX) $(CXXFLAGS) -o main main_code.o loss.o IO.o

main_code.o: main_code.cpp loss.h IO.h
	$(CXX) $(CXXFLAGS) -c main_code.cpp

loss.o: loss.h

IO.o: IO.h

clean:
	rm *.o