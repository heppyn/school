CXX=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11 -pthread
LD=g++
LDFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11 -pthread

all: hepneluk

run: compile
	
compile: all
	rm -f *.o *~ core
	

hepneluk: solution.o
	$(LD) $(LDFLAGS) $^ -o hepneluk

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f *.o *~ core


solution.o: solution.cpp
