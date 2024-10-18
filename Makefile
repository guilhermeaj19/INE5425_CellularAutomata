
CXX = g++ -std=c++11
CXXFLAGS = -Wall -g -fopenmp

SRCS = main.cpp cellular_automata.cpp color_terminal.cpp
OBJS = $(SRCS:.cpp=.o)

EXEC = automata

all: clean $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm -f $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)
