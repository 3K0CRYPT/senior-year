CXX=g++
SOURCE=$(wildcard *.cpp)
OBJECT=$(SOURCE:.cpp=.o)
BINARY=$(SOURCE:.cpp=)
CXXFLAGS=--std=c++14

%.o:%.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $% $< -o$@ 

all:$(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(BINARY)

clean:
	rm -f $(OBJECT) 

