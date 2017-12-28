CXX=g++
CXX_FLAGS=-Wall -Werror
CXX_LIBS=-lboost_system -lpthread
OBJS=main.o scanner.o

whatisopen: $(OBJS)
	$(CXX) -o whatisopen $^ $(CXX_FLAGS) $(CXX_LIBS)

%.o: %.cpp %.h
	$(CXX) -c -o $@ $< $(CXX_FLAGS) $(CXX_LIBS)

.PHONY: clean
clean:
	rm -f *.o whatisopen
