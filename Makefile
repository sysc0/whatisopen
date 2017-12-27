CXX=g++
CXX_FLAGS=-o whatisopen -Wall -Werror
CXX_LIBS=-lboost_system -lpthread

whatisopen: main.cpp scanner.h
	$(CXX) main.cpp $(CXX_FLAGS) $(CXX_LIBS)
