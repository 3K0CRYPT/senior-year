CXX = "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe"
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

